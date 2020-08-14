#include "color.h"

using namespace gc;

bool Color::invalid(int v)
{
	return 255 < v || v < 0;
}

Color::Color(unsigned long color)
{
	this->color = color;
	this->_red = GetRValue(color);
	this->_green = GetGValue(color);
	this->_blue = GetBValue(color);
}

Color::Color(int red, int green, int blue)
{
	this->_red = red;
	this->_green = green;
	this->_blue = blue;
	if (!this->isNull())
	{
		this->color = RGB(red, green, blue);
	}
}

Color::Color()
{
	Color(0, 0, 0);
}

int Color::red()
{
	return this->_red;
}

int Color::green()
{
	return this->_green;
}

int Color::blue()
{
	return this->_blue;
}

unsigned long Color::RGBQUAD2COLORREF(RGBQUAD rgbq)
{
	return Color::RGB2COLORREF(rgbq.rgbRed, rgbq.rgbGreen, rgbq.rgbBlue);
}

int Color::getRedValue(unsigned long color)
{
	return GetRValue(color);
}

int Color::getGreenValue(unsigned long color)
{
	return GetGValue(color);
}

int Color::getBlueValue(unsigned long color)
{
	return GetBValue(color);
}

Color Color::fromBitmap(LPBITMAP lpBitmap, int x, int y)
{
	if (!lpBitmap)
	{
		return INVALID_COLOR;
	}
	LPBYTE array = (LPBYTE)lpBitmap->bmBits;
	int offset = x * lpBitmap->bmBitsPixel / 8 + y * lpBitmap->bmWidthBytes;
	return Color(array[offset + 2], array[offset + 1], array[offset]);
}

unsigned long Color::colorref()
{
	return this->color;
}

unsigned long Color::RGB2COLORREF(int red, int green, int blue)
{
	return RGB(red, green, blue);
}

bool Color::operator==(const Color c)
{
	return this->_red == c._red && this->_green == c._green && this->_blue == c._blue;
}

bool Color::operator!=(const Color c)
{
	return this->_red != c._red || this->_green != c._green || this->_blue != c._blue;
}

std::string Color::toString()
{
	return "Color{red=" +
		std::to_string(this->_red) +
		", green=" +
		std::to_string(this->_green) +
		", blue=" +
		std::to_string(this->_blue) +
		"}";
}

bool Color::isNull()
{
	return this->invalid(this->_red) || this->invalid(this->_green) || this->invalid(this->_blue);
}




