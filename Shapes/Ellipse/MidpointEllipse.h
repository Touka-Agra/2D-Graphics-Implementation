
#ifndef MidpointEllipse_H
#define MidpointEllipse_H

#include <Windows.h>
#include <algorithm>
#include <cmath>

using namespace std;

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

void DrawMidpointEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c)
{
    int x = 0;
    int y = b;

    double a2 = a * a;
    double b2 = b * b;
    double dx = 2 * b2 * x;
    double dy = 2 * a2 * y;

    double d1 = b2 - a2 * b + 0.25 * a2;

    while (dx - dy < 0)
    {
        draw4Points(hdc, xc, yc, x, y, c);

        if (d1 < 0)
        {
            x++;
            dx += 2 * b2;
            d1 += dx + b2;
        }
        else
        {
            x++;
            y--;
            dx += 2 * b2;
            dy -= 2 * a2;
            d1 += dx - dy + b2;
        }
    }

    double d2 = b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2;

    while (y >= 0)
    {
        draw4Points(hdc, xc, yc, x, y, c);

        if (d2 > 0)
        {
            y--;
            dy -= 2 * a2;
            d2 += a2 - dy;
        }
        else
        {
            y--;
            x++;
            dx += 2 * b2;
            dy -= 2 * a2;
            d2 += dx - dy + a2;
        }
    }
}

#endif