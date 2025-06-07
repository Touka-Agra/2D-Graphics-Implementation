//
// Created by Aber on 6/5/2025.
//

#ifndef PR_RECTANGEL_H
#define PR_RECTANGEL_H

#include <windows.h>
#include <vector>
#include <cmath>
#include "../../Classes/Point.h"

using namespace std;

// Draw DrawSquare rectangle outline using two points:
// points[0] = upper-left vertex position
// points[1] = upper-right vertex position
void DrawRectangle(HDC hdc, vector<Point> points, COLORREF c) {
    if (points.size() < 2) return;

    // Get the upper-left vertex position
    int x1 = (int)points[0].x;
    int y1 = (int)points[0].y;

    // Calculate the width from the distance between the two points
    int dx = (int)(points[1].x - points[0].x);
    int dy = (int)(points[1].y - points[0].y);
    int width = (int)sqrt(dx * dx + dy * dy);
    int height = width / 2;  // Make height half of width for DrawSquare standard rectangle

    // Top edge
    for (int i = 0; i < width; i++) {
        SetPixel(hdc, x1 + i, y1, c);
    }

    // Bottom edge
    for (int i = 0; i < width; i++) {
        SetPixel(hdc, x1 + i, y1 + height - 1, c);
    }

    // Left edge
    for (int j = 0; j < height; j++) {
        SetPixel(hdc, x1, y1 + j, c);
    }

    // Right edge
    for (int j = 0; j < height; j++) {
        SetPixel(hdc, x1 + width - 1, y1 + j, c);
    }
}

#endif //PR_RECTANGEL_H