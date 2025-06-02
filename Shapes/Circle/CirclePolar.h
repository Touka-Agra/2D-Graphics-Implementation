//
// Created by Lenovo on 6/1/2025.
//

#ifndef CIRCLEPOLAR_H
#define CIRCLEPOLAR_H
#include <windows.h>
#include <cmath>
#include <vector>
#include "../../Classes/Point.h"


void drawCirclePolar(HDC hdc, std::vector<Point> points, COLORREF color) {
    if(points.size() < 2) return;
    int xc = points[0].x;
    int yc = points[0].y;
    int dx = points[1].x - xc;
    int dy = points[1].y - yc;
    int R = static_cast<int>(sqrt(dx*dx + dy*dy));


        double dtheta = 1.0 / R;
        for (double theta = 0; theta < 6.28; theta += dtheta) {
            int x = xc + R * cos(theta);
            int y = yc + R * sin(theta);
            SetPixel(hdc,x,y,color);
        }
    }

#endif //CIRCLEPOLAR_H
