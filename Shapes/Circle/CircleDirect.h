#ifndef CIRCLEDIRECT_H
#define CIRCLEDIRECT_H

#include <windows.h>
#include <cmath>
#include <vector>
#include "../../Classes/Point.h"
#include "eightPoint.h"

void drawCircleDirect(HDC hdc, std::vector<Point> points, COLORREF color) {
    if(points.size() < 2) return;
    int xc = points[0].x;
    int yc = points[0].y;
    int dx = points[1].x - xc;
    int dy = points[1].y - yc;
    int R = static_cast<int>(sqrt(dx*dx + dy*dy));

    int x = 0;
    int y = R;
    int R2 = R * R;
    
    while (x <= y) {
       draw8Points(hdc,xc,yc,x,y,color);
        
        x++;
        y = static_cast<int>(sqrt(R2 - x*x) + 0.5); // Round to nearest
    }
}

#endif