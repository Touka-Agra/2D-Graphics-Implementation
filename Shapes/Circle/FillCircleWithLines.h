#ifndef FILLCIRCLEWITHLINES_H
#define FILLCIRCLEWITHLINES_H

#include <windows.h>
#include <cmath>
#include <vector>
#include "../../Classes/Point.h"

#include "CircleModifiedMidpoint.h"


void fillQuarterCircleWithLines(HDC hdc, std::vector<Point> points, COLORREF color) {
    drawCircleModifiedMidpoint(hdc, {points[0], points[1]}, color);

    int xc = points[0].x;
    int yc = points[0].y;
    int dx = points[1].x - xc;
    int dy = points[1].y - yc;
    int R = static_cast<int>(sqrt(dx*dx + dy*dy));

    int xp = points[2].x;
    int yp = points[2].y;

    bool right = (xp > xc);
    bool bottom = (yp > yc);

    // Fill the quarter circle with lines
    for(int x = 0; x <= R; x++) {
        int y = static_cast<int>(sqrt(R*R - x*x));

        if(right && bottom) { // Bottom-right quarter
            drawDDALine(hdc, {Point(xc, yc + y), Point(xc + x, yc + y)}, color);
            drawDDALine(hdc, {Point(xc + x, yc), Point(xc + x, yc + y)}, color);
        }
        else if(!right && bottom) { // Bottom-left quarter
            drawDDALine(hdc, {Point(xc - x, yc), Point(xc - x, yc + y)}, color);
            drawDDALine(hdc, {Point(xc - x, yc + y), Point(xc, yc + y)}, color);
        }
        else if(right && !bottom) { // Top-right quarter
            drawDDALine(hdc, {Point(xc, yc - y), Point(xc + x, yc - y)}, color);
            drawDDALine(hdc, {Point(xc + x, yc - y), Point(xc + x, yc)}, color);
        }
        else { // Top-left quarter
            drawDDALine(hdc, {Point(xc - x, yc - y), Point(xc, yc - y)}, color);
            drawDDALine(hdc, {Point(xc - x, yc - y), Point(xc - x, yc)}, color);
        }
    }
}

#endif // FILLCIRCLEWITHLINES_H