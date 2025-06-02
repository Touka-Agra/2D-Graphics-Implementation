//
// Created by sh2 on 26-May-25.
//

#ifndef BEZIER_H
#define BEZIER_H

#include <windows.h>
#include <cmath>
#include <vector>
#include "../Classes/Point.h"

using namespace std;


Point BezierPoint(vector<Point> points, double t) {
    double u = 1 - t;

    double x = pow(u, 3) * points[0].x +
               3 * t * pow(u, 2) * points[1].x +
               3 * pow(t, 2) * u * points[2].x +
               pow(t, 3) * points[3].x;

    double y = pow(u, 3) * points[0].y +
               3 * t * pow(u, 2) * points[1].y +
               3 * pow(t, 2) * u * points[2].y +
               pow(t, 3) * points[3].y;

    return Point(x, y);
}

void DrawBezier(HDC hdc, vector<Point> points, COLORREF c) {
    for (double t = 0; t < 1; t += 0.00005) {
        Point newPoint = BezierPoint(points, t);
        SetPixel(hdc, (int) newPoint.x, (int) newPoint.y, c);
    }
}
#endif

//COLORREF InterpolateColor(COLORREF c1, COLORREF c2, double t) {
//    BYTE r1 = GetRValue(c1);
//    BYTE g1 = GetGValue(c1);
//    BYTE b1 = GetBValue(c1);
//
//    BYTE r2 = GetRValue(c2);
//    BYTE g2 = GetGValue(c2);
//    BYTE b2 = GetBValue(c2);
//
//    BYTE r = (BYTE) ((1 - t) * r1 + t * r2);
//    BYTE g = (BYTE) ((1 - t) * g1 + t * g2);
//    BYTE b = (BYTE) ((1 - t) * b1 + t * b2);
//
//    return RGB(r, g, b);
//}
//
//COLORREF Interpolate4Colors(COLORREF c0, COLORREF c1, COLORREF c2, COLORREF c3, double t) {
//    if (t < 0.33)
//        return InterpolateColor(c0, c1, t / 0.33);
//    else if (t < 0.66)
//        return InterpolateColor(c1, c2, (t - 0.33) / 0.33);
//    else
//        return InterpolateColor(c2, c3, (t - 0.66) / 0.33);
//
//}
