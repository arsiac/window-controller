
size.o:
	g++ -c -o size.o window-controller/size.cpp

point.o:
	g++ -c -o point.o window-controller/point.cpp

color.o:
	g++ -c -o color.o window-controller/color.cpp

bitmap.o:
	g++ -c -o bitmap.o window-controller/bitmap.cpp

windowcontrol.o:
	g++ -c -o windowcontrol.o window-controller/windowcontrol.cpp

package: size.o point.o color.o bitmap.o windowcontrol.o
	ar rcs window-controller.a *.o

clean:
	del *.o