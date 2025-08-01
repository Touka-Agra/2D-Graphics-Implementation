#ifndef ConvexFill_H
#define ConvexFill_H

#include <Windows.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include "../Classes/Point.h"

using namespace std;

#define MAXENTRIES 600
struct Entry
{
    int xmin, xmax;
};

void InitEntries(Entry table[])
{
    for (int i = 0; i < MAXENTRIES; i++)
    {

        table[i].xmin = MAXINT;
        table[i].xmax = -MAXINT;
    }
}

void ScanEdge(Point v1, Point v2, Entry table[])
{
    if (v1.y == v2.y)
        return;
    if (v1.y > v2.y)
        swap(v1, v2);
    double minv = (double)(v2.x - v1.x) / (v2.y - v1.y);
    double x = v1.x;
    int y = v1.y;
    while (y < v2.y)
    {
        if (x < table[y].xmin)
            table[y].xmin = (int)ceil(x);
        if (x > table[y].xmax)
            table[y].xmax = (int)floor(x);
        y++;
        x += minv;
    }
}

void DrawSanLines(HDC hdc, Entry table[], COLORREF color)
{
    for (int y = 0; y < MAXENTRIES; y++)
        if (table[y].xmin < table[y].xmax)
            for (int x = table[y].xmin; x <= table[y].xmax; x++)
                SetPixel(hdc, x, y, color);
}

void ConvexFill(HDC hdc, vector<Point> p, COLORREF color)
{
    int n = p.size();
    Entry *table = new Entry[MAXENTRIES];
    InitEntries(table);
    Point v1 = p[n - 1];
    for (int i = 0; i < n; i++)
    {
        Point v2 = p[i];
        ScanEdge(v1, v2, table);
        v1 = p[i];
    }
    DrawSanLines(hdc, table, color);
    delete table;
}

#endif