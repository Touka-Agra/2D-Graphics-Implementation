//
// Created by LENOVO on 5/28/2025.
//

#ifndef INC_2D_GRAPHICS_IMPLEMENTATION_POINT_H
#define INC_2D_GRAPHICS_IMPLEMENTATION_POINT_H


#include <windows.h>
#include <cmath>
#include "../../Classes/Point.h"
//window[0] ==> xleft ,, window[1] ==> xright ,, window[2] ==> ytop ,, window[3] ==> ybottom
bool drawClippedPoint(HDC hdc, vector<Point> p, vector<int>window , COLORREF c) {
    int xleft = window[0]; int xright = window[1];
    int ytop = window[2]; int ybottom = window[3];
    if ((p[0].x >= xleft) && (p[0].x <= xright) && (p[0].y >= ytop) && (p[0].y <= ybottom)) {
        SetPixel(hdc, round(p[0].x), round(p[0].y), c);
        return true;
    }
    return false;
}

#endif //INC_2D_GRAPHICS_IMPLEMENTATION_POINT_H
