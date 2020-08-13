#include "size.h"

using namespace gc;

Size::Size(int width, int height)
{
	this->_width = width;
	this->_height = height;
}

Size::Size()
{
	Size(0, 0);
}

bool Size::isNull()
{
	return this->_width < 0 || this->_height < 0;
}

bool Size::isEmpty()
{
	return this->_width == 0 || this->_height == 0;
}

int Size::width()
{
	return this->_width;
}

int Size::height()
{
	return this->_height;
}

bool Size::equal(int width, int height)
{
	return this->_width == width && this->_height == height;
}

Size Size::operator+(const Size s)
{
	return Size(this->_width + s._width, this->_height + s._height);
}

Size Size::operator-(const Size s)
{
	return Size(this->_width - s._width, this->_height - s._height);
}

bool Size::operator==(const Size s)
{
	return this->equal(s._width, s._height);
}

bool Size::operator!=(const Size s)
{
	return this->_width != s._width || this->_height != s._height;
}

std::string Size::toString()
{
	return "(" +
		std::to_string(this->_width) +
		"," +
		std::to_string(this->_height) +
		")";
}
