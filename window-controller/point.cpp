#include "point.h"

using namespace gc;

Point::Point(long x, long y)
{
	this->_x = x;
	this->_y = y;
}

Point::Point()
{
	Point(0, 0);
}

long Point::x()
{
	return this->_x;
}

long Point::y()
{
	return this->_y;
}

bool Point::isOverflow()
{
	return this->_x < 0 || this->_y < 0;
}

bool Point::equal(long x, long y)
{
	return this->_x == x && this->_y == y;
}

long Point::makeLong()
{
	return (this->_x & 0xffff) | ((this->_y & 0xffff) << 16);
}

Point Point::operator+(const Point p)
{
	return Point(this->_x + p._x, this->_y + p._y);
}

Point Point::operator-(const Point p)
{
	return Point(this->_x - p._x, this->_y - p._y);
}

bool Point::operator==(const Point p)
{
	return this->equal(p._x, p._y);
}

bool Point::operator!=(const Point p)
{
	return this->_x != p._x || this->_y != p._y;
}

std::string Point::toString()
{
	return "(" +
		std::to_string(this->_x) +
		"," +
		std::to_string(this->_y) +
		")";
}
