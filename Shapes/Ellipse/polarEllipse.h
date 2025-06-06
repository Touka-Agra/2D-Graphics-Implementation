#ifndef polarEllipse_H
#define polarEllipse_H

#include <windows.h>
#include <algorithm>
#include <cmath>
#include "draw4points.h"

void DrawPolarEllipse(HDC hdc, vector<Point>points, COLORREF color)
{
    int xc = points[0].x;
    int yc = points[0].y;
    int a = points[1].x;
    int b = points[1].y;

    int R = 10000;
    double dTheta = 1.0 / R;
    double cd = cos(dTheta);
    double sd = sin(dTheta);

    double x = a;
    double y = 0;

    while (x > 0)
    {
        int rx = round(x);
        int ry = round(y);

        draw4Points(hdc, xc, yc, rx, ry, color);

        double xtemp = x * cd - (a * y * sd) / b;
        y = y * cd + (b * x * sd) / a;
        x = xtemp;
    }
}

#endif