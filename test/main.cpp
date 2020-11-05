#include <windowcontrol.h>
#include <iostream>
#include <bitmap.h>

int main()
{
	using namespace gc;
	using namespace std;
	// NotePad Class Name
	const char *cname = "NotePad";
	WindowControl wc(cname);
	if (wc.useless())
	{
		cout << "cannot get " << cname << wc.getHandle() << endl;
		return 1;
	}
	cout << "handle: " << wc.getHandle() << endl;

	// Find Window By API
	HWND hwnd = FindWindow(cname, 0);
	cout << "hwnd: " << hwnd << endl;

	RECT rect;
	if (!GetWindowRect(wc.getHandle(), &rect))
	{
		cout << "get rect failed" << endl;
	}
	else
	{
		cout << "rect: " << "top->" << rect.top
			<< ", right->" << rect.right
			<< ", buttom->" << rect.bottom
			<< ", left->" << rect.left
			<< endl;
	}

	Point windowPosition = wc.location();
	cout << "position: " << windowPosition.toString() << endl;
	if (windowPosition.isOverflow())
	{
		cout << "position overflow" << endl;
	}
	
	Size windowSize = wc.size();
	cout << "size: " << windowSize.toString() << endl;

	if (windowSize.isNull())
	{
		cout << "get window size failed" << endl;
	}

	if (!wc.resize(1200, 700))
	{
		cout << "resize window failed" << endl;
	}

	HBITMAP hBitmap = wc.bitmap(Point(0, 0), wc.clientSize());
	Bitmap::save(hBitmap, "C:\\Users\\arsia\\Desktop\\a.bmp");
	return 0;
}