#include <Windows.h>
#include <algorithm>
#include <cmath>

int Round(double x)
{
    return (int)(x + 0.5);
}

void draw4Points(HDC hdc, int xc, int yc, int px, int py, COLORREF c)
{
    SetPixel(hdc, xc + px, yc + py, c);
    SetPixel(hdc, xc - px, yc + py, c);
    SetPixel(hdc, xc + px, yc - py, c);
    SetPixel(hdc, xc - px, yc - py, c);
}

void DrawPolarEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF color)
{
    int R = 10000;
    double dTheta = 1.0 / R;
    double cd = cos(dTheta);
    double sd = sin(dTheta);

    double x = a;
    double y = 0;

    while (x > 0)
    {
        int rx = Round(x);
        int ry = Round(y);

        draw4Points(hdc, xc, yc, rx, ry, color);

        double xtemp = x * cd - (a * y * sd) / b;
        y = y * cd + (b * x * sd) / a;
        x = xtemp;
    }
}