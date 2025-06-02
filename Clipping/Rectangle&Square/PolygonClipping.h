//
// Created by LENOVO on 5/29/2025.
//

#ifndef INC_2D_GRAPHICS_IMPLEMENTATION_POLYGONCLIPPING_H
#define INC_2D_GRAPHICS_IMPLEMENTATION_POLYGONCLIPPING_H


#include <windows.h>
#include <cmath>
#include <vector>
#include "../../Classes/Point.h"

using namespace std;

typedef vector<Point> VertixList;
typedef bool (*IsInFunc)(Point& v, int edge);
typedef Point(*IntersectFunc)(Point& v1, Point& v2, int edge);

VertixList ClipwEdge(VertixList p, int edge, IsInFunc In, IntersectFunc Intersect) {
    VertixList outList;
    int n = p.size();
    Point v1 = p[n - 1];
    bool v1_in = In(v1, edge);
    for (int i = 0; i < n; i++) {
        Point v2 = p[i];
        bool v2_in = In(v2, edge);
        if (v1_in && v2_in) {
            outList.push_back(v2);
        }
        else if (v2_in) {
            outList.push_back(Intersect(v1, v2, edge));
            outList.push_back(v2);
        }
        else if (v1_in) {
            outList.push_back(Intersect(v1, v2, edge));
        }
        v1 = v2;
        v1_in = v2_in;
    }
    return outList;
}

bool InLeft(Point& v, int edge) {
    return v.x >= edge;
}

bool InRight(Point& v, int edge) {
    return v.x <= edge;
}

bool InTop(Point& v, int edge) {
    return v.y >= edge;
}

bool InBottom(Point& v, int edge) {
    return v.y <= edge;
}

Point VIntersect(Point& v1, Point& v2, int xedge) {
    Point res;
    res.x = xedge;
    res.y = v1.y + (xedge - v1.x) * (v2.y - v1.y) / (v2.x - v1.x);
    return res;
}
Point HIntersect(Point& v1, Point& v2, int yedge)
{
    Point res;
    res.y = yedge;
    res.x = v1.x + (yedge - v1.y) * (v2.x - v1.x) / (v2.y - v1.y);
    return res;
}

vector<Paint> drawClippedPolygon(HDC hdc, vector<Point>p, vector<int>window, COLORREF c) {
    int xleft = window[0];
    int xright = window[1];
    int ytop = window[2];
    int ybottom = window[3];
    VertixList vlist;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        vlist.push_back(p[i]);
    }

    // Clipping the polygon progressively with each edge of the rectangle
    vlist = ClipwEdge(vlist, xleft, InLeft, VIntersect);
    vlist = ClipwEdge(vlist, xright, InRight, VIntersect);
    vlist = ClipwEdge(vlist, ytop, InTop, HIntersect);
    vlist = ClipwEdge(vlist, ybottom, InBottom, HIntersect);

    // Drawing the clipped polygon
    vector<Paint> polygon;
    Point v1 = vlist[vlist.size() - 1];
    for (int i = 0; i < (int)vlist.size(); ++i) {
        Point v2 = vlist[i];
        drawBresenhamLine(hdc, {{v1.x, v1.y}, {v2.x, v2.y}}, c);
        Paint paint = Paint(ID_SHAPE_LINE_MIDPOINT, {{v1.x, v1.y}, {v2.x, v2.y}}, c);
        polygon.push_back(paint);
        v1 = v2;

    }

    return polygon;
}

#endif //INC_2D_GRAPHICS_IMPLEMENTATION_POLYGONCLIPPING_H
