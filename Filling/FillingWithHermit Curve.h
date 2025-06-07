#ifndef FILLINGWITHHERMITCURVE_H
#define FILLINGWITHHERMITCURVE_H

#include <windows.h>
#include <vector>
#include <cmath>
#include "../Classes/Point.h"

using namespace std;

// Fill a square with vertical Hermite curves
// points[0] = point inside the square
void FillSquareWithHermiteCurve(HDC hdc, vector<Point> points, COLORREF c) {
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
    const int spacing = 3;  // Spacing between vertical curves

    // Draw vertical Hermite curves across the square
    for (int i = left; i <= right; i += spacing) {
        // Control points for the Hermite curve
        double P0 = top;                    // Start point
        double P1 = bottom;                 // End point

        // Tangent vectors for the Hermite curve (reduced to stay within borders)
        double height = bottom - top;
        double T0 = height * 0.25;   // Start tangent (25% of height)
        double T1 = height * 0.25;   // End tangent (25% of height)

        // Alternate curve direction for each line
        if ((i - left) % (spacing * 2) == 0) {
            T0 = -T0;  // Reverse start tangent
            T1 = -T1;  // Reverse end tangent
        }

        // Draw the curve with smaller step size for smoother appearance
        for (double t = 0; t <= 1; t += 0.001) {
            // Hermite basis functions
            double h1 = 2 * t * t * t - 3 * t * t + 1;  // For P0
            double h2 = -2 * t * t * t + 3 * t * t;     // For P1
            double h3 = t * t * t - 2 * t * t + t;      // For T0
            double h4 = t * t * t - t * t;              // For T1

            // Calculate point on the curve using Hermite formula
            double y = h1 * P0 + h2 * P1 + h3 * T0 + h4 * T1;

            // Only draw if the point is within the square boundaries
            if (y >= top && y <= bottom) {
                SetPixel(hdc, i, (int)y, c);
            }
        }
    }
}

#endif //FILLINGWITHHERMITCURVE_H
