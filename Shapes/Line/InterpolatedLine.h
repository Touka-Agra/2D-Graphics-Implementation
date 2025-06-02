//
// Created by Lenovo on 6/1/2025.
//

#ifndef INTERPOLATEDLINE_H
#define INTERPOLATEDLINE_H

#endif //INTERPOLATEDLINE_H

#include <windows.h>
#include <cmath>
#include <vector>
#include "../../Classes/Point.h"
using namespace std;

void drawParametricLine(HDC hdc, vector<Point> p, COLORREF c) {
    int x1 = p[0].x, y1 = p[0].y;
    int x2 = p[1].x, y2 = p[1].y;



    int steps = max(abs(x2 - x1), abs(y2 - y1));
    if (steps == 0) steps = 1;

    for (int i = 0; i <= steps; ++i) {
        float t = (float)i / steps;


        int x = round(x1 + t * (x2 - x1));
        int y = round(y1 + t * (y2 - y1));


        SetPixel(hdc, x, y, c);
    }
}
