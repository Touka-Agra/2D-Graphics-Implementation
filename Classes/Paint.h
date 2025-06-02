//
// Created by sh2 on 26-May-25.
//

#ifndef PROJECT_PAINT_H
#define PROJECT_PAINT_H

#include <iostream>
#include <windows.h>
#include <vector>
#include "Point.h"

using namespace std;

class Paint{
private:
    int type;
    vector<Point> points;
    COLORREF color;

public:
    Paint(int type, vector<Point> points, COLORREF color): type(type), points(points), color(color){}
    int getType() const { return type; }
    const vector<Point>& getPoints() const { return points; }
    COLORREF getColor(){return color;}
    int getNumOfPoints(){return points.size();}
};


#endif //PROJECT_PAINT_H
