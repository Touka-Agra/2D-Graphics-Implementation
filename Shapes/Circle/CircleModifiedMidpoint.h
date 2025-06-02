//
// Created by Lenovo on 6/1/2025.
//

#ifndef CIRCLEMODIFIEDMIDPOINT_H
#define CIRCLEMODIFIEDMIDPOINT_H

#include <windows.h>
#include <cmath>
#include <vector>
#include "../../Classes/Point.h"
#include "eightPoint.h"

void drawCircleModifiedMidpoint(HDC hdc, std::vector<Point> points, COLORREF color) {
    if(points.size() < 2) return;
    int xc = points[0].x;
    int yc = points[0].y;
    int dx = points[1].x - xc;
    int dy = points[1].y - yc;
    int R = static_cast<int>(sqrt(dx*dx + dy*dy));

    int x = 0;
    int y = R;
    int d = 1 - R;
    int d1 = 3;
    int d2 = 5 - 2 * R;

    while (x <= y) {
        draw8Points(hdc, xc, yc, x, y, color);

        if (d < 0) {
            d += d1;
            d2 += 2;
        } else {
            d += d2;
            d2 += 4;
            y--;
        }
        d1 += 2;
        x++;
    }
}

#endif // CIRCLEMODIFIEDMIDPOINT_H