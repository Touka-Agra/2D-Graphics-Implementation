//
// Created by Aber on 6/5/2025.
//

#ifndef PR_SQUARE_H
#define PR_SQUARE_H

#include <windows.h>
#include <vector>
#include <cmath>
#include "../../Classes/Point.h"

using namespace std;

// Draw DrawSquare square outline using two points:
// points[0] = upper-left vertex position
// points[1] = upper-right vertex position
void DrawSquare(HDC hdc, vector<Point> points, COLORREF c) {
    if (points.size() < 2) return;

    // Get the upper-left vertex position
    int x1 = (int)points[0].x;
    int y1 = (int)points[0].y;

    // Calculate the side length from the distance between the two points
    int dx = (int)(points[1].x - points[0].x);
    int dy = (int)(points[1].y - points[0].y);
    int size = (int)sqrt(dx * dx + dy * dy);

    // Top edge
    for (int i = 0; i < size; i++) {
        SetPixel(hdc, x1 + i, y1, c);
    }

    // Bottom edge
    for (int i = 0; i < size; i++) {
        SetPixel(hdc, x1 + i, y1 + size - 1, c);
    }

    // Left edge
    for (int j = 0; j < size; j++) {
        SetPixel(hdc, x1, y1 + j, c);
    }

    // Right edge
    for (int j = 0; j < size; j++) {
        SetPixel(hdc, x1 + size - 1, y1 + j, c);
    }
}

#endif //PR_SQUARE_H