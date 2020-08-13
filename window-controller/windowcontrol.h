#ifndef WINDOWCONTROL_H
#define WINDOWCONTROL_H
#include <windows.h>
#include "color.h"
#include "size.h"
#include "point.h"

namespace gc {

#define MOVEWINDOW_REPAINT TRUE

	class WindowControl
	{
	private:
		HWND handle;
		HDC dc;

	public:
		WindowControl(HWND handle);
#ifdef UNICODE
		WindowControl(const wchar_t* className);
#else
		WindowControl(const char* className);
#endif // UNICODE

		WindowControl();

		HWND getHandle();
		HDC getDC();
		bool releaseDC(HDC hdc);
		HDC getWindowDC();
		bool useless();
		bool isInvalid();
		Size size();
		Size clientSize();
		Point location();
		bool resize(int width, int height);
		bool resizeClient(int width, int height);
		bool move(int x, int y);
		bool moveWindow(int x, int y, int width, int height);
		Color pixel(int x, int y);
		HBITMAP bitmap(int x, int y, int width, int height);
		HBITMAP bitmap(Point point, Size size);

		// background mouse event
		void leftClick(int x, int y);
		void rightClick(int x, int y);
	};
}

#endif // WINDOWCONTROL_H
