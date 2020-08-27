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

		WindowControl(const char* className);

		WindowControl();

		void fromName(const char* className);
		void fromHandle(HWND handle);
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
		bool resize(Size s);

		bool resizeClient(int width, int height);
		bool resizeClient(Size s);

		bool move(int x, int y);
		bool move(Point p);

		bool moveWindow(int x, int y, int width, int height);
		bool moveWindow(Point p, Size s);

		unsigned long getPixel(int x, int y);

		Color pixel(int x, int y);
		Color pixel(Point p);

		HBITMAP bitmap(int x, int y, int width, int height);
		HBITMAP bitmap(Point point, Size size);

		// background mouse event
		void leftClick(int x, int y);
		void leftClick(Point p);
		void rightClick(int x, int y);
		void rightClick(Point p);
	};
}

#endif // WINDOWCONTROL_H
