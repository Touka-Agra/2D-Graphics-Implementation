//
// Created by LENOVO on 6/5/2025.
//

#ifndef INC_2D_GRAPHICS_IMPLEMENTATION_LINECLIP_H
#define INC_2D_GRAPHICS_IMPLEMENTATION_LINECLIP_H

#include <windows.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include "../../Classes/Point.h"
//#include "../../Shapes/Line/BresenhamLine.h"
#include "IsPointIn.h"
#include "../../Classes/Paint.h"
#include "../../ToolBar/MenuIDs.h"

using namespace std;
int clipLineWithCircle(double x1, double y1, double x2, double y2, int cx, int cy, int r, double& ix1, double& iy1, double& ix2, double& iy2) {
    // Translate system to make circle center at origin
    x1 -= cx;
    y1 -= cy;
    x2 -= cx;
    y2 -= cy;

    double dx = x2 - x1;
    double dy = y2 - y1;
    double dr = sqrt(dx * dx + dy * dy);
    double D = x1 * y2 - x2 * y1;

    double discriminant = r * r * dr * dr - D * D;

    if (discriminant < 0) {
        return 0; // no intersection
    }

    double sqrtDiscriminant = sqrt(discriminant);

    ix1 = round((D * dy + (dy < 0 ? -1 : 1) * dx * sqrtDiscriminant) / (dr * dr)) + cx;
    iy1 = round((-D * dx + fabs(dy) * sqrtDiscriminant) / (dr * dr)) + cy;

    if (discriminant == 0) {
        return 1; // one intersection (tangent)
    }

    ix2 = round((D * dy - (dy < 0 ? -1 : 1) * dx * sqrtDiscriminant) / (dr * dr)) + cx;
    iy2 = round((-D * dx - fabs(dy) * sqrtDiscriminant) / (dr * dr)) + cy;

    return 2; // two intersections
}

// Clip and draw the line inside the circle
Paint drawClippedLineC(HDC hdc, vector<Point> points, vector<int> window, COLORREF c) {
    double x1 = points[0].x, y1 = points[0].y;
    double x2 = points[1].x, y2 = points[1].y;
    int cx = window[0], cy = window[1], r = window[2];

    bool p1Inside = isPointInsideCircle(x1, y1, cx, cy, r);
    bool p2Inside = isPointInsideCircle(x2, y2, cx, cy, r);

    Point clippedStart, clippedEnd;
    bool draw = false;

    if (p1Inside && p2Inside) {
        // Both points inside
        clippedStart = {x1, y1};
        clippedEnd = {x2, y2};
        draw = true;
    } else {
        double ix1, iy1, ix2, iy2;
        int intersections = clipLineWithCircle(x1, y1, x2, y2, cx, cy, r, ix1, iy1, ix2, iy2);

        if (intersections == 0) {
            if (p1Inside || p2Inside) {
                // Should not occur based on logic — defensive
            }
        } else if (intersections == 1) {
            // Tangent - skip drawing
        } else {
            if (p1Inside) {
                double d1 = (ix1 - x1)*(ix1 - x1) + (iy1 - y1)*(iy1 - y1);
                double d2 = (ix2 - x1)*(ix2 - x1) + (iy2 - y1)*(iy2 - y1);
                clippedStart = {x1, y1};
                clippedEnd = (d1 < d2) ? Point{ix1, iy1} : Point{ix2, iy2};
                draw = true;
            } else if (p2Inside) {
                double d1 = (ix1 - x2)*(ix1 - x2) + (iy1 - y2)*(iy1 - y2);
                double d2 = (ix2 - x2)*(ix2 - x2) + (iy2 - y2)*(iy2 - y2);
                clippedStart = (d1 < d2) ? Point{ix1, iy1} : Point{ix2, iy2};
                clippedEnd = {x2, y2};
                draw = true;
            } else {
                // Both outside - draw between valid intersections
                bool i1Valid = ((ix1 >= min(x1, x2) && ix1 <= max(x1, x2)) &&
                                (iy1 >= min(y1, y2) && iy1 <= max(y1, y2)));
                bool i2Valid = ((ix2 >= min(x1, x2) && ix2 <= max(x1, x2)) &&
                                (iy2 >= min(y1, y2) && iy2 <= max(y1, y2)));
                if (i1Valid && i2Valid) {
                    clippedStart = {ix1, iy1};
                    clippedEnd = {ix2, iy2};
                    draw = true;
                }
            }
        }
    }

    vector<Point> p = {{clippedStart.x, clippedStart.y}, {clippedEnd.x, clippedEnd.y}};
    if (draw) {
        drawBresenhamLine(hdc, p, c);
        Paint paint = Paint(ID_SHAPE_LINE_MIDPOINT, p, c);
        return paint;
    }
    return Paint(0,p,c);
}

#endif //INC_2D_GRAPHICS_IMPLEMENTATION_LINECLIP_H
