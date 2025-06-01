//
// Created by Lenovo on 6/1/2025.
//

#ifndef CIRCLEMIDPOINT_H
#define CIRCLEMIDPOINT_H

#include <windows.h>
#include <cmath>
#include <vector>
#include "../../Classes/Point.h"
#include "eightPoint.h"

void drawCircleMidpoint(HDC hdc, std::vector<Point> points, COLORREF color) {
    if(points.size() < 2) return;
    int xc = points[0].x;
    int yc = points[0].y;
    int dx = points[1].x - xc;
    int dy = points[1].y - yc;
    int R = static_cast<int>(sqrt(dx*dx + dy*dy));

    int x = 0;
    int y = R;
    int d = 1 - R;

    while (x <= y) {
        draw8Points(hdc, xc, yc, x, y, color);

        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

#endif // CIRCLEMIDPOINT_H