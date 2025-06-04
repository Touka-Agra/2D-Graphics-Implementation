#ifndef FILLCIRCLEWITHCIRCLES_H
#define FILLCIRCLEWITHCIRCLES_H

#include <windows.h>
#include <cmath>
#include <vector>
#include "../../Classes/Point.h"
#include "eightPoint.h"
#include "CircleModifiedMidpoint.h"

void fillQuarterCircleWithCircles(HDC hdc, std::vector<Point> points, COLORREF color) {
    if(points.size() < 3) return;

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

    for(int r = R; r > 0; r--) {
        int x = r;
        int y = 0;
        int d = 1 - r;

        while(x >= y) {
            if(right && bottom) { // Bottom-right quarter
                SetPixel(hdc, xc + x, yc + y, color);
                SetPixel(hdc, xc + y, yc + x, color);
            }
            else if(!right && bottom) { // Bottom-left quarter
                SetPixel(hdc, xc - x, yc + y, color);
                SetPixel(hdc, xc - y, yc + x, color);
            }
            else if(right && !bottom) { // Top-right quarter
                SetPixel(hdc, xc + x, yc - y, color);
                SetPixel(hdc, xc + y, yc - x, color);
            }
            else { // Top-left quarter
                SetPixel(hdc, xc - x, yc - y, color);
                SetPixel(hdc, xc - y, yc - x, color);
            }

            if(d < 0) {
                d += 2 * y + 3;
            } else {
                d += 2 * (y - x) + 5;
                x--;
            }
            y++;
        }
    }
}

#endif // FILLCIRCLEWITHCIRCLES_H