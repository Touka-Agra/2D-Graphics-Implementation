#ifndef CIRCLEDIRECT_H
#define CIRCLEDIRECT_H

#include <windows.h>
#include <cmath>
#include <vector>
#include "eightPoint.h"

void drawCircleDirect(HDC hdc, vector<Point> points, COLORREF color){
    Point p1 = points[0];
    Point p2 = points[1];

    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;

    double R = sqrt(dx*dx + dy*dy);

    double x = 0, y = R;
    double R2 = R * R;

    while (x <= y) {
       draw8Points(hdc,(int)p1.x,(int)p2.y,x,y,color);
        
        x++;
        y = static_cast<int>(sqrt(R2 - x*x) + 0.5); // Round to nearest
    }
}

#endif