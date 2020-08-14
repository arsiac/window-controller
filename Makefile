
size.o:
	g++ -c -o size.o -I window-controller window-controller/size.cpp

point.o:
	g++ -c -o point.o -I window-controller window-controller/point.cpp

color.o:
	g++ -c -o color.o -I window-controller window-controller/color.cpp

bitmap.o:
	g++ -c -o bitmap.o -I window-controller window-controller/bitmap.cpp

windowcontrol.o:
	g++ -c -o windowcontrol.o -I window-controller window-controller/windowcontrol.cpp

package: size.o point.o color.o bitmap.o windowcontrol.o
	ar rcs libwindow-controller.a *.o

clean:
	del *.o