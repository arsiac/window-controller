#include "windowcontrol.h"
#include <iostream>

using namespace std;
using namespace gc;

WindowControl::WindowControl(HWND handle)
{
	this->handle = handle;
	this->dc = this->getDC();
}

#ifdef UNICODE

WindowControl::WindowControl(const wchar_t* className)
{
	this->handle = ::FindWindowW(className, 0);
	this->dc = this->getDC();
}

#else

WindowControl::WindowControl(const char* className)
{
	this->handle = ::FindWindowA(className, 0);
	this->dc = this->getDC();
}

#endif // UNICODE

WindowControl::WindowControl()
{
	WindowControl((HWND)INVALID_HANDLE_VALUE);
}

HWND WindowControl::getHandle()
{
	return this->handle;
}

HDC WindowControl::getDC()
{
	if (this->isInvalid())
	{
		cout << "WindowControl::getDC() => isInvalid() -> true" << endl;
		return NULL;
	}
	return ::GetDC(this->handle);
}

bool WindowControl::releaseDC(HDC hdc)
{
	return ::ReleaseDC(this->handle, hdc);
}

HDC WindowControl::getWindowDC()
{
	if (this->isInvalid())
	{
		cout << "WindowControl::getWindowDC() => isInvalid() -> true" << endl;
		return NULL;
	}
	return ::GetWindowDC(this->handle);
}

bool WindowControl::useless()
{
	return this->isInvalid() || this->handle == 0;
}

bool WindowControl::isInvalid()
{
	return this->handle == INVALID_HANDLE_VALUE;
}

Size WindowControl::size()
{
	if (this->isInvalid())
	{
		cout << "WindowControl::size() => isInvalid() -> true" << endl;
		return Size(-1, -1);
	}
	RECT rect;
	if (!::GetWindowRect(this->handle, &rect))
	{
		cout << "WindowControl::size() => GetWindowRect() -> false" << endl;
		/*cout << "\trect: top->" << rect.top << ", left->" << rect.left
			<< ", bottom->" << rect.bottom << ", right: " << rect.right << endl;*/
		return Size(-1, -1);
	}
	return Size(rect.right - rect.left, rect.bottom - rect.top);
}

Size WindowControl::clientSize()
{
	if (this->isInvalid())
	{
		cout << "WindowControl::clientSize() => isInvalid() -> true" << endl;
		return Size(0, 0);
	}
	RECT rect;
	if (!::GetClientRect(this->handle, &rect))
	{
		cout << "WindowControl::clientSize() => GetClientRect() -> false" << endl;
		return Size(0, 0);
	}
	return Size(rect.right - rect.left, rect.bottom - rect.top);
}

Point WindowControl::location()
{
	if (this->isInvalid())
	{
		cout << "WindowControl::location() => isInvalid() -> true" << endl;
		return Point(-1, -1);
	}
	RECT rect;
	if (!::GetWindowRect(this->handle, &rect))
	{
		cout << "WindowControl::location() => GetWindowRect() -> false" << endl;
		return Point(-1, -1);
	}
	return Point(rect.left, rect.top);
}

bool WindowControl::resize(int width, int height)
{
	if (this->useless())
	{
		cout << "WindowControl::resize() => useless() -> true" << endl;
		return false;
	}
	Point location = this->location();
	if (location.isOverflow())
	{
		cout << "WindowControl::resize() => location.isOverflow() -> true" << endl;
		return false;
	}
	return ::MoveWindow(this->handle, location.x(), location.y(), width, height, MOVEWINDOW_REPAINT);
}

bool WindowControl::resizeClient(int width, int height)
{
	if (this->useless())
	{
		cout << "WindowControl::resizeClient() => useless() -> true" << endl;
		return false;
	}
	Point location = this->location();
	if (location.isOverflow())
	{
		cout << "WindowControl::resizeClient() => location.isOverflow(() -> true" << endl;
		return false;
	}
	Size borderSize = this->size() - this->clientSize();
	return ::MoveWindow(this->handle, location.x(), location.y(), width + borderSize.width(), height + borderSize.height(), MOVEWINDOW_REPAINT);
}

bool WindowControl::move(int x, int y)
{
	if (this->useless())
	{
		cout << "WindowControl::move() => useless() -> true" << endl;
		return false;
	}
	Size size = this->size();
	if (size.isNull())
	{
		cout << "WindowControl::move() => size.isNull() -> true" << endl;
		return false;
	}
	return ::MoveWindow(this->handle, x, y, size.width(), size.height(), MOVEWINDOW_REPAINT);
}

bool WindowControl::moveWindow(int x, int y, int width, int height)
{
	if (this->useless())
	{
		cout << "WindowControl::moveWindow() => useless() -> true" << endl;
		return false;
	}
	return ::MoveWindow(this->handle, x, y, width, height, MOVEWINDOW_REPAINT);
}

Color WindowControl::pixel(int x, int y)
{
	if (this->isInvalid())
	{
		cout << "WindowControl::pixel() => isInvalid() -> true" << endl;
		return INVALID_COLOR;
	}
	if (!this->dc)
	{
		cout << "WindowControl::pixel() => this->dc -> NULL (1)" << endl;
		this->dc = this->getDC();
		if (!this->dc)
		{
			cout << "WindowControl::pixel() => this->dc -> NULL (2)" << endl;
			return INVALID_COLOR;
		}
	}
	return Color(::GetPixel(this->dc, x, y));
}

HBITMAP WindowControl::bitmap(int x, int y, int width, int height)
{
	HDC hdc = this->getDC();
	if (!hdc || width == 0 || height == 0)
	{
		cout << "WindowControl::bitmap() => hdc -> NULL || width -> 0 || height -> 0" << endl;
		return NULL;
	}

	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height);
	HDC hdcMemory = CreateCompatibleDC(hdc);

	::SelectObject(hdcMemory, hBitmap);
	if (!::BitBlt(hdcMemory, 0, 0, width, height, hdc, x, y, SRCCOPY))
	{
		cout << "WindowControl::bitmap() => BitBlt() -> false" << endl;
		::DeleteDC(hdcMemory);
		this->releaseDC(hdc);
		return NULL;
	}
	::DeleteDC(hdcMemory);
	this->releaseDC(hdc);
	return hBitmap;
}


HBITMAP WindowControl::bitmap(Point point, Size size)
{
	return this->bitmap(point.x(), point.y(), size.width(), size.height());
}


void WindowControl::leftClick(int x, int y)
{
	long position = MAKELPARAM(x, y);
	PostMessage(this->handle, WM_MOUSEMOVE, MK_LBUTTON, position);
	PostMessage(this->handle, WM_LBUTTONDOWN, MK_LBUTTON, position);
	PostMessage(this->handle, WM_LBUTTONUP, MK_LBUTTON, position);
}

void WindowControl::rightClick(int x, int y)
{
	long position = MAKELPARAM(x, y);
	PostMessage(this->handle, WM_MOUSEMOVE, MK_RBUTTON, position);
	PostMessage(this->handle, WM_RBUTTONDOWN, MK_RBUTTON, position);
	PostMessage(this->handle, WM_RBUTTONUP, MK_RBUTTON, position);
}