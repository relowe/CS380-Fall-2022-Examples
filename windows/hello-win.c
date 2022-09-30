#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInst, 
                     HINSTANCE hInstPrev, 
                     PSTR cmdline, 
                     int cmdshow) 
{
    while(1) {
    MessageBox(NULL, "Hello, world", "caption",
    MB_ABORTRETRYIGNORE|MB_ICONERROR);
    }
}
