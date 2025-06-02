//
// Created by LENOVO on 5/28/2025.
//

#ifndef INC_2D_GRAPHICS_IMPLEMENTATION_BRESENHAMLINE_H
#define INC_2D_GRAPHICS_IMPLEMENTATION_BRESENHAMLINE_H


#include <windows.h>
#include <cmath>
#include "../../Classes/Point.h"

void drawBresenhamLine(HDC hdc, vector<Point> p, COLORREF c) {
    int x1 = p[0].x; int x2 = p[1].x;
    int y1= p[0].y; int y2=p[1].y;
    int x = x1, y = y1;
    int dx, dy, d, d1, d2;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    SetPixel(hdc, x, y, c);
    int xinc = (x1 < x2) ? 1 : -1;
    int yinc = (y1 < y2) ? 1 : -1;
    if (dy <= dx) { //slope <= 1 || slope >= -1
        d = dx - 2 * dy;
        d1 = -2 * dy; //d>0
        d2 = 2 * (dx - dy); //d>0
        while (x != x2) {
            if (d > 0) {
                d += d1;
            }
            else {
                d += d2;
                y += yinc;
            }
            x += xinc;
            SetPixel(hdc, x, y, c);
        }
    }
    else { //slope > 1 || slope < -1
        d = 2 * dx - dy;
        d1 = 2 * dx; //d<0
        d2 = 2 * (dx - dy); //d>0
        while (y != y2) {
            if (d > 0) {
                d += d2;
                x += xinc;
            }
            else {
                d += d1;
            }
            y += yinc;
            SetPixel(hdc, x, y, c);
        }
    }
}

#endif //INC_2D_GRAPHICS_IMPLEMENTATION_BRESENHAMLINE_H

