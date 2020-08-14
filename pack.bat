rmdir /q /s .\Release\window-controller

md .\Release\window-controller\
md .\Release\window-controller\include\

copy .\window-controller\*.h .\Release\window-controller\include\
copy .\Release\window-controller.lib .\Release\window-controller\
copy .\libwindow-controller.a .\Release\window-controller\