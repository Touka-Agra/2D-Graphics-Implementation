#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <vector>
#include "ToolBar/ToolBar.h"
#include "ToolBar/MenuIDs.h"
#include "ToolBar/Draw.h"
#include "Classes/Point.h"

using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK
WindowProcedure(HWND, UINT, WPARAM, LPARAM
);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

int WINAPI
WinMain(HINSTANCE
        hThisInstance,
        HINSTANCE hPrevInstance,
        LPSTR
        lpszArgument,
        int nCmdShow
) {

    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    cout << "Console initialized" << endl;
    Sleep(2000);


    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);

    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));

    if (!RegisterClassEx(&wincl))
        return 0;

    hwnd = CreateWindowEx(
            0,
            szClassName,
            _T("Touka Mohamed Korany 20220094"),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            544,
            375,
            HWND_DESKTOP,
            NULL,
            hThisInstance,
            NULL
    );

    ShowWindow(hwnd, nCmdShow);

    while (GetMessage(&messages, NULL, 0, 0)) {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

HDC hdc;

vector<Point> points;

int userChoice;
int needPoints;

LRESULT CALLBACK
WindowProcedure(HWND
                hwnd,
                UINT message,
                WPARAM wParam,
                LPARAM lParam
) {
    switch (message) {
        case WM_LBUTTONDOWN: {
            double x = LOWORD(lParam);
            double y = HIWORD(lParam);

            if (userChoice != NULL) {
                Point point = Point(x, y);
                points.push_back(point);
            }

            if (points.size() == needPoints) {
                std::cout << "Draw function called with " << points.size() << " points\n";

                hdc = GetDC(hwnd);
                draw(hdc, userChoice, points);
                ReleaseDC(hwnd, hdc);

                points.clear();
            }
            break;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_CREATE:
            createToolBar(hwnd);
            break;

        case WM_COMMAND:
            points.clear();
            userChoice = LOWORD(wParam);
            cout << "User Choice: "<< userChoice << endl;
            needPoints = mapOfNeedPoints[userChoice];
            if (needPoints == 0) {
                hdc = GetDC(hwnd);
                draw(hdc, userChoice, points);
                ReleaseDC(hwnd, hdc);
            }
            break;

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
