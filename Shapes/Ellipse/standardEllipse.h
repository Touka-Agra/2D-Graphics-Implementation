
#ifndef standardEllipse_H
#define standardEllipse_H

#include <Windows.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include "../../Classes/Point.h"
#include "draw4points.h"

using namespace std;

#include <Windows.h>
#include <algorithm>
#include <cmath>

using namespace std;

void DrawEllipse(HDC hdc, vector<Point>points, COLORREF c)
{
    int xc = points[0].x;
    int yc = points[0].y;
    int a = abs(xc -points[1].x);
    int b = abs(yc-points[1].y);
    double step = 0.5;

    for (double x = 0; x <= a; x += step)
    {

        double y = b * sqrt(1.0 - (x * x) / (a * a));

        int px = round(x);
        int py = round(y);

        draw4Points(hdc, xc, yc, px, py, c);
    }
}

#endif
