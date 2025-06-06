//
// Created by LENOVO on 6/5/2025.
//

#ifndef INC_2D_GRAPHICS_IMPLEMENTATION_DRAW4POINTS_H
#define INC_2D_GRAPHICS_IMPLEMENTATION_DRAW4POINTS_H

#include <windows.h>
#include <algorithm>
#include <cmath>

void draw4Points(HDC hdc, int xc, int yc, int px, int py, COLORREF c)
{
    SetPixel(hdc, xc + px, yc + py, c);
    SetPixel(hdc, xc - px, yc + py, c);
    SetPixel(hdc, xc + px, yc - py, c);
    SetPixel(hdc, xc - px, yc - py, c);
}

#endif //INC_2D_GRAPHICS_IMPLEMENTATION_DRAW4POINTS_H
