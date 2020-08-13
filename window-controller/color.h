#ifndef COLOR_H
#define COLOR_H
#include <windows.h>
#include <string>
#include <windows.h>

namespace gc {

#define INVALID_COLOR Color(-1, -1, -1)

	class Color
	{
	private:
		int _red;
		int _green;
		int _blue;
		COLORREF color;
		inline bool invalid(int v);

	public:
		Color(COLORREF color);
		Color(int red, int green, int blue);
		Color();
		int red();
		int green();
		int blue();
		COLORREF colorref();
		bool operator==(const Color c);
		bool operator!=(const Color c);
		std::string toString();
		bool isNull();

		static COLORREF RGB2COLORREF(int red, int green, int blue);
		static COLORREF RGBQUAD2COLORREF(RGBQUAD rgbq);
		static int getRedValue(COLORREF color);
		static int getGreenValue(COLORREF color);
		static int getBlueValue(COLORREF color);
		static Color fromBitmap(LPBITMAP lpBitmap, int x, int y);
	};
}

#endif // COLOR_H
