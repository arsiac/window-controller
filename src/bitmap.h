#ifndef BITMAP_H
#define BITMAP_H
#include<windows.h>

namespace gc {
	class Bitmap
	{
	public:
		static bool save(HBITMAP hBitmap, const char* path);
		static LPBITMAP getBitmapData(HBITMAP hBitmap, HDC dc);
	};
}

#endif // BITMAP_H
