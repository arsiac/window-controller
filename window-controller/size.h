#ifndef SIZE_H
#define SIZE_H
#include <string>

namespace gc {
	class Size
	{
	private:
		int _width;
		int _height;
	public:
		Size(int width, int height);
		Size();
		bool isNull();
		bool isEmpty();
		int width();
		int height();
		bool equal(int width, int height);
		Size operator+(const Size s);
		Size operator-(const Size s);
		bool operator==(const Size s);
		bool operator!=(const Size s);
		std::string toString();
	};
}

#endif // SIZE_H
