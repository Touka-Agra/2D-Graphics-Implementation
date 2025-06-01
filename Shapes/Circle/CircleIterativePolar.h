//
// Created by Lenovo on 6/1/2025.
//

#ifndef CIRCLEITERATIVEPOLAR_H
#define CIRCLEITERATIVEPOLAR_H
#include <windows.h>
#include <cmath>
#include <vector>
#include "../../Classes/Point.h"
#include "eightPoint.h"

void drawCircleIterativePolar(HDC hdc,std::vector<Point> points, COLORREF color) {
    if(points.size() < 2) return;
    int xc = points[0].x;
    int yc = points[0].y;
    int dx = points[1].x - xc;
    int dy = points[1].y - yc;
    int R = static_cast<int>(sqrt(dx*dx + dy*dy));
    double x = R;
    double y = 0;
    double dtheta = 1.0 / R;
    double cd = cos(dtheta);
    double sd = sin(dtheta);

    while (x >= y) {
       draw8Points(hdc, xc, yc,x,y, color);

        double x1 = x * cd - y * sd;
        y = x * sd + y * cd;
        x = x1;
    }
}
#endif //CIRCLEITERATIVEPOLAR_H
