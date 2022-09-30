// Compile With gcc window.c -o window.exe -lgdi32
#define UNICODE
#define _UNICODE
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

const TCHAR CLSNAME[] = TEXT("helloworldWClass");
LRESULT CALLBACK winproc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PSTR cmdline, int cmdshow)
{
    WNDCLASSEX wc = { };
    MSG msg;
    HWND hwnd;
    HWND hClickMe, hDontClickMe;
    int count = 0;

    wc.cbSize        = sizeof (wc);
    wc.style         = 0;
    wc.lpfnWndProc   = winproc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInst;
    wc.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = CLSNAME;
    wc.hIconSm       = LoadIcon (NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, TEXT("Could not register window class"), 
                  NULL, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_LEFT,
                          CLSNAME,
                          NULL,
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          640,
                          480,
                          NULL,
                          NULL,
                          hInst,
                          NULL);
    if (!hwnd) {
        MessageBox(NULL, TEXT("Could not create window"), NULL, MB_ICONERROR);
        return 0;
    }

    // make a huge button
    hClickMe = CreateWindow(L"BUTTON",
                            L"Click Me",
                            WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
                            10,   // x
                            10,   // y
                            290,  // width
                            420,  // height
                            hwnd, // parent
                            (HMENU) 42,   // hmenu
                            hInst, // our instance
                            NULL); // pointer to user data

    if (!hClickMe) {
        MessageBox(NULL, TEXT("Could not create button"), NULL, MB_ICONERROR);
        return 0;
    }


    hDontClickMe = CreateWindow(L"BUTTON",
                            L"Don't Click Me",
                            WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
                            300,   // x
                            10,   // y
                            290,  // width
                            420,  // height
                            hwnd, // parent
                            (HMENU) 43,   // hmenu
                            hInst, // our instance
                            NULL); // pointer to user data

    if (!hDontClickMe) {
        MessageBox(NULL, TEXT("Could not create button"), NULL, MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, cmdshow);
    UpdateWindow(hwnd);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}


LRESULT CALLBACK winproc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp)
{
    if(wm == WM_DESTROY) {
        PostQuitMessage(0);
    }

    if(wm == WM_COMMAND) {
        // maybe a button click
        if(HIWORD(wp) == BN_CLICKED) {
            // it is a button click!
            switch(LOWORD(wp)) {
            case 42:
                MessageBox(hwnd, TEXT("Thank you."), L"Button Message", MB_OK);
                break;
            case 43:
                MessageBox(hwnd, TEXT("What's wrong with you? I told you not to click me!"), L"Button Complaint", MB_ICONERROR);
                PostQuitMessage(-1);
                break;
            }
        }
    }
    return DefWindowProc(hwnd, wm, wp, lp);
}
