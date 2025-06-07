#ifndef FILLINGWITHBEZIERCURVE_H
#define FILLINGWITHBEZIERCURVE_H

#include <windows.h>
#include <vector>
#include <cmath>
#include "../Classes/Point.h"

using namespace std;

// Fill a square with horizontal Bezier curves
// points[0] = point inside the square
void FillRectangleWithBezierCurve(HDC hdc, vector<Point> points, COLORREF c) {
    if (points.empty()) return;

    // Get the point inside the square
    Point p = points[0];

    // Get the color at the given point
    COLORREF pointColor = GetPixel(hdc, (int)p.x, (int)p.y);

    // Find square borders by scanning for color changes
    int left = (int)p.x;
    int right = (int)p.x;
    int top = (int)p.y;
    int bottom = (int)p.y;

    // Scan left
    while (left > 0 && GetPixel(hdc, left, (int)p.y) == pointColor) {
        left--;
    }
    left++; // Move back to the last point with same color

    // Scan right
    while (GetPixel(hdc, right, (int)p.y) == pointColor) {
        right++;
    }
    right--; // Move back to the last point with same color

    // Scan up
    while (top > 0 && GetPixel(hdc, (int)p.x, top) == pointColor) {
        top--;
    }
    top++; // Move back to the last point with same color

    // Scan down
    while (GetPixel(hdc, (int)p.x, bottom) == pointColor) {
        bottom++;
    }
    bottom--; // Move back to the last point with same color

    // Spacing between curves
    const int spacing = 3;  // Spacing between horizontal curves

    // Draw horizontal Bezier curves across the square
    for (int j = top; j <= bottom; j += spacing) {
        // Control points for the Bezier curve
        double P0 = left;                    // Start point
        double P1 = left + (right - left)/3;  // First control point
        double P2 = left + 2*(right - left)/3; // Second control point
        double P3 = right;                   // End point

        // Add vertical offset to control points for curve shape
        double height = bottom - top;
        double offset = height * 0.15;  // 15% of the height for curve amplitude

        // Alternate curve direction for each line
        if ((j - top) % (spacing * 2) == 0) {
            P1 = P1 - offset;  // Move first control point up
            P2 = P2 - offset;  // Move second control point up
        } else {
            P1 = P1 + offset;  // Move first control point down
            P2 = P2 + offset;  // Move second control point down
        }

        // Draw the curve with smaller step size for smoother appearance
        for (double t = 0; t <= 1; t += 0.001) {
            // Bezier basis functions
            double b0 = (1 - t) * (1 - t) * (1 - t);
            double b1 = 3 * t * (1 - t) * (1 - t);
            double b2 = 3 * t * t * (1 - t);
            double b3 = t * t * t;

            // Calculate point on the curve
            double x = b0 * P0 + b1 * P1 + b2 * P2 + b3 * P3;

            // Draw the point
            SetPixel(hdc, (int)x, j, c);
        }
    }
}

#endif //FILLINGWITHBEZIERCURVE_H
