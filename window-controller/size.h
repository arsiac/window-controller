#ifndef SIZE_H
#define SIZE_H
#include <string>

namespace gc {
	class Size
	{
	private:
		long _width;
		long _height;
	public:
		Size(long width, long height);
		Size();
		bool isNull();
		bool isEmpty();
		long width();
		long height();
		bool equal(long width, long height);
		Size operator+(const Size s);
		Size operator-(const Size s);
		bool operator==(const Size s);
		bool operator!=(const Size s);
		std::string toString();
	};
}

#endif // SIZE_H
