//
// Created by sh2 on 26-May-25.
//

#ifndef PROJECT_PAINT_H
#define PROJECT_PAINT_H

#include <iostream>
#include <vector>
#include "Point.h"

using namespace std;

class Paint{
private:
    int type;
    vector<Point> points;

public:
    Paint(int type, vector<Point> points): type(type), points(points){}
    int getType() const { return type; }
    const vector<Point>& getPoints() const { return points; }
};


#endif //PROJECT_PAINT_H
