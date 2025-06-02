
#ifndef standardEllipse_H
#define standardEllipse_H

#include <Windows.h>
#include <algorithm>
#include <cmath>

using namespace std;

int Round(double x)
{
    return (int)(x + 0.5);
}

void draw4Points(HDC hdc, int centerX, int centerY, int px, int py, COLORREF c)
{
    SetPixel(hdc, centerX + px, centerY + py, c);
    SetPixel(hdc, centerX - px, centerY + py, c);
    SetPixel(hdc, centerX + px, centerY - py, c);
    SetPixel(hdc, centerX - px, centerY - py, c);
}
void DrawEllipse(HDC hdc, int centerX, int centerY, int a, int b, COLORREF c)
{
    double step = 0.5;

    for (double x = 0; x <= a; x += step)
    {

        double y = b * sqrt(1.0 - (x * x) / (a * a));

        int px = Round(x);
        int py = Round(y);

        draw4Points(hdc, centerX, centerY, px, py, c);
    }
}

#endif