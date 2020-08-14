#ifndef POINT_H
#define POINT_H
#include <string>

namespace gc {
	class Point
	{
	private:
		long _x;
		long _y;
	public:
		Point(long x, long y);
		Point();
		long x();
		long y();
		bool isOverflow();
		bool equal(long x, long y);
		long makeLong();
		Point operator+(const Point p);
		Point operator-(const Point p);
		bool operator==(const Point p);
		bool operator!=(const Point p);
		std::string toString();
	};
}

#endif // POINT_H
