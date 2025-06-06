//
// Created by Aber on 6/4/2025.
//

#ifndef PR_CARDINALSPLINECURVE_H
#define PR_CARDINALSPLINECURVE_H
#include <windows.h>
#include <cmath>
#include <vector>
#include "../Classes/Point.h"

using namespace std;

Point HermitePoint(Point P0, Point T0, Point P1, Point T1, double t) {
    double t2 = t * t;
    double t3 = t2 * t;

    // Hermite basis functions
    double h1 = 2 * t3 - 3 * t2 + 1;
    double h2 = -2 * t3 + 3 * t2;
    double h3 = t3 - 2 * t2 + t;
    double h4 = t3 - t2;

    double x = h1 * P0.x + h2 * P1.x + h3 * T0.x + h4 * T1.x;
    double y = h1 * P0.y + h2 * P1.y + h3 * T0.y + h4 * T1.y;

    return Point(x, y);
}

void DrawHermiteCurve(HDC hdc, Point P0, Point T0, Point P1, Point T1, COLORREF c) {
    for (double t = 0; t <= 1; t += 0.002) {
        Point point = HermitePoint(P0, T0, P1, T1, t);
        SetPixel(hdc, (int)point.x, (int)point.y, c);
        // Make dots slightly bigger for visibility
        SetPixel(hdc, (int)point.x + 1, (int)point.y, c);
        SetPixel(hdc, (int)point.x, (int)point.y + 1, c);
        SetPixel(hdc, (int)point.x + 1, (int)point.y + 1, c);
    }
}

void DrawCardinalSpline(HDC hdc, vector<Point> points, double tension, COLORREF c) {
    if (points.size() < 4) return;

    double c1 = 1 - tension;
    Point T0(c1 * (points[2].x - points[0].x), c1 * (points[2].y - points[0].y));

    for (int i = 2; i < points.size() - 1; i++) {
        Point T1(c1 * (points[i + 1].x - points[i - 1].x),
                 c1 * (points[i + 1].y - points[i - 1].y));
        DrawHermiteCurve(hdc, points[i - 1], T0, points[i], T1, c);
        T0 = T1;
    }
}

void DrawControlPoints(HDC hdc, vector<Point> points, COLORREF c) {
    int radius = 5;

    for (int i = 1; i < points.size()-1; i++) { // Not including first and last point
        int centerX = (int)points[i].x;
        int centerY = (int)points[i].y;

        // Draw filled circle
        for (int y = -radius; y <= radius; y++) {
            for (int x = -radius; x <= radius; x++) {
                if (x * x + y * y <= radius * radius) {
                    SetPixel(hdc, centerX + x, centerY + y, c);
                }
            }
        }
    }
}

#endif //PR_CARDINALSPLINECURVE_H


// Optional: Grid drawing function
//void DrawGrid(HDC hdc, int width, int height, int gridSize, COLORREF c) {
//    // Draw vertical lines
//    for (int x = 0; x < width; x += gridSize) {
//        for (int y = 0; y < height; y++) {
//            SetPixel(hdc, x, y, c);
//        }
//    }
//
//    // Draw horizontal lines
//    for (int y = 0; y < height; y += gridSize) {
//        for (int x = 0; x < width; x++) {
//            SetPixel(hdc, x, y, c);
//        }
//    }
//}