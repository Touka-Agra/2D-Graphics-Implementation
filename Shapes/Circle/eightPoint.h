//
// Created by Lenovo on 6/1/2025.
//

#ifndef EIGHTPOINT_H
#define EIGHTPOINT_H
#include <windows.h>
#include <cmath>
#include <vector>


void draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF color) {
    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc - x, yc + y, color);
    SetPixel(hdc, xc + x, yc - y, color);
    SetPixel(hdc, xc - x, yc - y, color);
    SetPixel(hdc, xc + y, yc + x, color);
    SetPixel(hdc, xc - y, yc + x, color);
    SetPixel(hdc, xc + y, yc - x, color);
    SetPixel(hdc, xc - y, yc - x, color);
}

#endif //EIGHTPOINT_H
