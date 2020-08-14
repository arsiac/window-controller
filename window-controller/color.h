#ifndef COLOR_H
#define COLOR_H
#include <windows.h>
#include <string>

namespace gc {

#define INVALID_COLOR Color(-1, -1, -1)

	class Color
	{
	private:
		int _red;
		int _green;
		int _blue;
		unsigned long color;
		inline bool invalid(int v);

	public:
		Color(unsigned long color);
		Color(int red, int green, int blue);
		Color();
		int red();
		int green();
		int blue();
		unsigned long colorref();
		bool operator==(const Color c);
		bool operator!=(const Color c);
		std::string toString();
		bool isNull();

		static unsigned long RGB2COLORREF(int red, int green, int blue);
		static unsigned long RGBQUAD2COLORREF(RGBQUAD rgbq);
		static int getRedValue(unsigned long color);
		static int getGreenValue(unsigned long color);
		static int getBlueValue(unsigned long color);
		static Color fromBitmap(LPBITMAP lpBitmap, int x, int y);
	};
}

#endif // COLOR_H
