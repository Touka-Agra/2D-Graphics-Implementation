//
// Created by LENOVO on 5/28/2025.
//

#ifndef INC_2D_GRAPHICS_IMPLEMENTATION_LINECLIPPING_H
#define INC_2D_GRAPHICS_IMPLEMENTATION_LINECLIPPING_H



#include <windows.h>
#include <cmath>
#include <vector>
#include "../../Classes/Point.h"
//#include "../../Shapes/Line/BresenhamLine.h"

using namespace std;

union OutCode {
    struct {
        unsigned left: 1;
        unsigned right: 1;
        unsigned top: 1;
        unsigned bottom: 1;

    };
    unsigned all: 4;
};

///////////////////////////////
OutCode getOutCode(double x, double y, int xleft, int xright, int ytop, int ybottom) {
    OutCode res;
    res.all = 0;
    if (x < xleft) res.left = 1;
    else if (x > xright) res.right = 1;

    if (y < ytop) res.top = 1;
    else if (y > ybottom) res.bottom = 1;

    return res;
}

///////////////////////////////
Point VIntersect(int xedge, Point &p1, Point &p2) {
    Point res;
    res.x = xedge;
    res.y = p1.y + (xedge - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
    return res;
}

///////////////////////////////
Point HIntersect(int yedge, Point &p1, Point &p2) {
    Point res;
    res.y = yedge;
    res.x = p1.x + (yedge - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
    return res;
}

///////////////////////////////
Paint drawClippedLine(HDC hdc, vector<Point>p, vector<int> window, COLORREF c) {
    //cohen-sutherland
    int xleft = window[0]; int xright = window[1];
    int ytop = window[2]; int ybottom =window[3];

    Point p1 = p[0];
    Point p2 = p[1];
    OutCode out1 = getOutCode(p1.x, p1.y, xleft, xright, ytop, ybottom);
    OutCode out2 = getOutCode(p2.x, p2.y, xleft, xright, ytop, ybottom);
    bool accept = false;
    while (true) {
        if (out1.all == 0 && out2.all == 0) {
            accept = true;
            break;
        }
        if ((out1.all & out2.all) != 0) {
            break;
        }
        if (out1.all != 0) {
            if (out1.left) p1 = VIntersect(xleft, p1, p2);
            else if (out1.right) p1 = VIntersect(xright, p1, p2);
            else if (out1.top) p1 = HIntersect(ytop, p1, p2);
            else if (out1.bottom) p1 = HIntersect(ybottom, p1, p2);
            out1 = getOutCode(p1.x, p1.y, xleft, xright, ytop, ybottom);
        } else {
            if (out2.left) p2 = VIntersect(xleft, p1, p2);
            else if (out2.right) p2 = VIntersect(xright, p1, p2);
            else if (out2.top) p2 = HIntersect(ytop, p1, p2);
            else if (out2.bottom) p2 = HIntersect(ybottom, p1, p2);
            out2 = getOutCode(p2.x, p2.y, xleft, xright, ytop, ybottom);
        }
    }
    p = {p1,p2};
    if (accept) {
        drawBresenhamLine(hdc, p, c);
        Paint paint = Paint(ID_SHAPE_LINE_MIDPOINT, p, c);
        return paint;
    }
    return Paint(0,p,c);
}

#endif //INC_2D_GRAPHICS_IMPLEMENTATION_LINECLIPPING_H



