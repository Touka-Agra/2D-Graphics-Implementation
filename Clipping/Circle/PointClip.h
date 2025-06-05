//
// Created by LENOVO on 6/5/2025.
//

#ifndef INC_2D_GRAPHICS_IMPLEMENTATION_POINTCLIP_H
#define INC_2D_GRAPHICS_IMPLEMENTATION_POINTCLIP_H

#include <windows.h>
#include <cmath>
#include <vector>
#include "../../Classes/Point.h"
#include "IsPointIn.h"


bool drawClippedPointC(HDC hdc, std::vector<Point>p,  std::vector<int>window, COLORREF c) {
    int cx = window[0];
    int cy = window[1];
    int r = window[2];
    if (isPointInsideCircle(p[0].x, p[0].y, cx, cy, r)) {
        SetPixel(hdc, round(p[0].x), round(p[0].y), c);
        return true;
    }
    return false;
}
#endif //INC_2D_GRAPHICS_IMPLEMENTATION_POINTCLIP_H
