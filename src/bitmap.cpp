#include "bitmap.h"

using namespace gc;

bool Bitmap::save(HBITMAP hBitmap, const char* path)
{
	if (hBitmap == NULL)
	{
		return false;
	}
	//  定义位图文件表头
	BITMAPFILEHEADER bitmapFileHeader;
	//  定义位图信息表头
	BITMAPINFOHEADER bitmapInfoHeader;

	//  调色板长度
	int nColorLen = 0;
	//  调色表大小
	DWORD dwRgbQuadSize = 0;
	//  位图大小
	DWORD dwBmSize = 0;
	//  分配内存的指针
	HGLOBAL    hMem = NULL;

	LPBITMAPINFOHEADER     lpBitmapFileHeader;

	BITMAP bitmap;

	HDC hDC;

	HANDLE hFile = NULL;

	DWORD dwWritten;

	::GetObject(hBitmap, sizeof(BITMAP), &bitmap);

	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);    // 本结构所占的字节
	bitmapInfoHeader.biWidth = bitmap.bmWidth;            // 位图宽
	bitmapInfoHeader.biHeight = bitmap.bmHeight;            // 位图高
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = bitmap.bmBitsPixel;    // 每一图素的位数
	bitmapInfoHeader.biCompression = BI_RGB;            // 不压缩
	bitmapInfoHeader.biSizeImage = 0;  //  位图大小
	bitmapInfoHeader.biXPelsPerMeter = 0;
	bitmapInfoHeader.biYPelsPerMeter = 0;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;

	//  计算位图图素数据区大小
	dwBmSize = 4 * ((bitmap.bmWidth * bitmapInfoHeader.biBitCount + 31) / 32) * bitmap.bmHeight;

	//  如果图素位 <= 8bit，则有调色板
	if (bitmapInfoHeader.biBitCount <= 8)
	{
		nColorLen = (1 << bitmap.bmBitsPixel);
	}

	//  计算调色板大小
	dwRgbQuadSize = nColorLen * sizeof(RGBQUAD);

	//  分配内存
	hMem = ::GlobalAlloc(GHND, dwBmSize + dwRgbQuadSize + sizeof(BITMAPINFOHEADER));

	if (NULL == hMem)
	{
		return false;
	}

	//  锁定内存
	lpBitmapFileHeader = (LPBITMAPINFOHEADER)GlobalLock(hMem);

	//  将bitmapInfoHeader中的内容写入分配的内存中
	*lpBitmapFileHeader = bitmapInfoHeader;


	hDC = ::GetDC(NULL);

	//  将位图中的数据以bits的形式放入lpData中。
	::GetDIBits(hDC, hBitmap, 0, (DWORD)bitmapInfoHeader.biHeight, (LPSTR)lpBitmapFileHeader + sizeof(BITMAPINFOHEADER) + dwRgbQuadSize, (BITMAPINFO*)lpBitmapFileHeader, (DWORD)DIB_RGB_COLORS);

	bitmapFileHeader.bfType = 0x4D42;  // 位图文件类型：BM
	bitmapFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwRgbQuadSize + dwBmSize;  // 位图大小
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	bitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwRgbQuadSize;  // 位图数据与文件头部的偏移量

	//  把上面的数据写入文件中

	hFile = ::CreateFileA(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return false;
	}

	//  写入位图文件头
	::WriteFile(hFile, (LPSTR)&bitmapFileHeader, sizeof(BITMAPFILEHEADER), (DWORD*)&dwWritten, NULL);
	//  写入位图数据
	::WriteFile(hFile, (LPBITMAPINFOHEADER)lpBitmapFileHeader, bitmapFileHeader.bfSize - sizeof(BITMAPFILEHEADER), (DWORD*)&dwWritten, NULL);

	::GlobalFree(hMem);
	::CloseHandle(hFile);

	return true;
}

LPBITMAP Bitmap::getBitmapData(HBITMAP hBitmap, HDC dc)
{
	if (!hBitmap)
	{
		return NULL;
	}

	if (!dc)
	{
		dc = GetDC(0);
	}

	LPBITMAP lpBitmap = (LPBITMAP)malloc(sizeof(BITMAP));
	if (!::GetObject(hBitmap, sizeof(BITMAP), lpBitmap))
	{
		free(lpBitmap);
		return NULL;
	}
	BITMAPINFO bitmapInfo;
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biWidth = lpBitmap->bmWidth;
	bitmapInfo.bmiHeader.biHeight = lpBitmap->bmHeight;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = lpBitmap->bmBitsPixel;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	bitmapInfo.bmiHeader.biSizeImage = lpBitmap->bmWidth * lpBitmap->bmHeight * (lpBitmap->bmBitsPixel / 8);
	bitmapInfo.bmiHeader.biClrUsed = 0;
	bitmapInfo.bmiHeader.biClrImportant = 0;

	lpBitmap->bmBits = malloc(bitmapInfo.bmiHeader.biSizeImage);
	if (!::GetDIBits(dc, hBitmap, 0, lpBitmap->bmHeight, lpBitmap->bmBits, &bitmapInfo, DIB_RGB_COLORS))
	{
		free(lpBitmap->bmBits);
		free(lpBitmap);
		return NULL;
	}

	return lpBitmap;
}
