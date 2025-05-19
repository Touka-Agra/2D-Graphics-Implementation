#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <cmath>
#include <vector>
#include <algorithm>

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
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.
            hInstance = hThisInstance;
    wincl.
            lpszClassName = szClassName;
    wincl.
            lpfnWndProc = WindowProcedure;
    wincl.
            style = CS_DBLCLKS;
    wincl.
            cbSize = sizeof(WNDCLASSEX);

    wincl.
            hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.
            hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.
            hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.
            lpszMenuName = NULL;
    wincl.
            cbClsExtra = 0;
    wincl.
            cbWndExtra = 0;
    wincl.
            hbrBackground = CreateSolidBrush(RGB(0, 0, 0));

    if (!
            RegisterClassEx(&wincl)
            )
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

    ShowWindow(hwnd, nCmdShow
    );

    while (
            GetMessage(&messages, NULL,
                       0, 0)) {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.
            wParam;
}

struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

COLORREF InterpolateColor(COLORREF c1, COLORREF c2, double t) {
    BYTE r1 = GetRValue(c1);
    BYTE g1 = GetGValue(c1);
    BYTE b1 = GetBValue(c1);

    BYTE r2 = GetRValue(c2);
    BYTE g2 = GetGValue(c2);
    BYTE b2 = GetBValue(c2);

    BYTE r = (BYTE) ((1 - t) * r1 + t * r2);
    BYTE g = (BYTE) ((1 - t) * g1 + t * g2);
    BYTE b = (BYTE) ((1 - t) * b1 + t * b2);

    return RGB(r, g, b);
}

COLORREF Interpolate4Colors(COLORREF c0, COLORREF c1, COLORREF c2, COLORREF c3, double t) {
    if (t < 0.33)
        return InterpolateColor(c0, c1, t / 0.33);
    else if (t < 0.66)
        return InterpolateColor(c1, c2, (t - 0.33) / 0.33);
    else
        return InterpolateColor(c2, c3, (t - 0.66) / 0.33);

}

Point BezierPoint(vector<Point> points, double t) {
    double u = 1 - t;

    double x = pow(u, 3) * points[0].x +
               3 * t * pow(u, 2) * points[1].x +
               3 * pow(t, 2) * u * points[2].x +
               pow(t, 3) * points[3].x;

    double y = pow(u, 3) * points[0].y +
               3 * t * pow(u, 2) * points[1].y +
               3 * pow(t, 2) * u * points[2].y +
               pow(t, 3) * points[3].y;

    return Point(x, y);
}

void DrawBezier(HDC hdc, vector<Point> points, vector<COLORREF> colors) {
    for (double t = 0; t < 1; t += 0.00005) {
        Point newPoint = BezierPoint(points, t);
        COLORREF c = Interpolate4Colors(colors[0], colors[1], colors[2], colors[3], t);
        SetPixel(hdc, (int) newPoint.x, (int) newPoint.y, c);
    }
}

int cnt = 0;
vector<Point> points;
vector<COLORREF> colors = {
        RGB(0, 0, 255),
        RGB(255, 0, 0),
        RGB(255, 255, 0),
        RGB(0, 255, 0)
};


LRESULT CALLBACK
WindowProcedure(HWND
                hwnd,
                UINT message, WPARAM
                wParam,
                LPARAM lParam
) {
    switch (message) {
        case WM_LBUTTONDOWN: {
            double x = LOWORD(lParam);
            double y = HIWORD(lParam);

            Point point = Point(x, y);
            points.
                    push_back(point);

            cnt++;
            if (cnt == 4) {
                HDC hdc = GetDC(hwnd);
                DrawBezier(hdc, points, colors
                );
                ReleaseDC(hwnd, hdc
                );
                cnt = 0;
                points.

                        clear();

            }


            break;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return
                    DefWindowProc(hwnd, message, wParam, lParam
                    );
    }

    return 0;
}
