//
// Created by Lenovo on 6/1/2025.
//

#ifndef DDALINE_H
#define DDALINE_H

#endif //DDALINE_H

#include <windows.h>
#include <cmath>
#include <vector>
#include "../../Classes/Point.h"
using namespace std;

void drawDDALine(HDC hdc, vector<Point> p, COLORREF c) {
  int x1 = p[0].x, y1 = p[0].y;
  int x2 = p[1].x, y2 = p[1].y;

  int dx = x2 - x1;
  int dy = y2 - y1;

  int steps = max(abs(dx), abs(dy));

  float xInc = dx / (float) steps;
  float yInc = dy / (float) steps;

  float x = x1;
  float y = y1;

  for (int i = 0; i <= steps; i++) {
    SetPixel(hdc, round(x), round(y), c);
    x += xInc;
    y += yInc;
  }
}

