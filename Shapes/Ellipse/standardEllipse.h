
#ifndef standardEllipse_H
#define standardEllipse_H

#include <Windows.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include "../../Classes/Point.h"

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
void DrawEllipse(HDC hdc, vector<Point> points, COLORREF c)
{
    double centerX = points[0].x;
    double centerY = points[0].y;
    double a = points[1].x;
    double b = points[1].y;

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