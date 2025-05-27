#include <windows.h>
#include <iostream>
#include <vector>
#include "MenuIDs.h"
#include "../Classes/Point.h"
#include "../Curves/Bezier.h"

using namespace std;

void draw(HDC hdc, int userChoice, vector<Point> points, COLORREF color) {
    switch (userChoice) {
        // ===== Line =====
        case ID_SHAPE_LINE_DDA:
            cout << "DDA Line has been drawn\n\n";
            break;
        case ID_SHAPE_LINE_MIDPOINT:
            cout << "Midpoint Line has been drawn\n\n";
            break;
        case ID_SHAPE_LINE_PARAM:
            cout << "Parametric Line has been drawn\n\n";
            break;

            // ===== Circle =====
        case ID_SHAPE_CIRCLE_DIRECT:
            cout << "Direct Circle has been drawn\n\n";
            break;
        case ID_SHAPE_CIRCLE_POLAR:
            cout << "Polar Circle has been drawn\n\n";
            break;
        case ID_SHAPE_CIRCLE_IT_POLAR:
            cout << "Iterative Polar Circle has been drawn\n\n";
            break;
        case ID_SHAPE_CIRCLE_MIDPOINT:
            cout << "Midpoint Circle has been drawn\n\n";
            break;
        case ID_SHAPE_CIRCLE_MOD_MIDPOINT:
            cout << "Modified Midpoint Circle has been drawn\n\n";
            break;
        case ID_SHAPE_CIRCLE_FILL_LINES:
            cout << "Filled Circle with Lines has been drawn\n\n";
            break;
        case ID_SHAPE_CIRCLE_FILL_CIRCLES:
            cout << "Filled Circle with Circles has been drawn\n\b";
            break;

            // ===== Ellipse =====
        case ID_SHAPE_ELLIPSE_DIRECT:
            cout << "Direct Ellipse has been drawn\n\n";
            break;
        case ID_SHAPE_ELLIPSE_POLAR:
            cout << "Polar Ellipse has been drawn\n\n";
            break;
        case ID_SHAPE_ELLIPSE_MIDPOINT:
            cout << "Midpoint Ellipse has been drawn\n\n";
            break;

            // ===== Square =====
        case ID_SHAPE_SQUARE_DRAW:
            cout << "Square has been drawn\n\n";
            break;
        case ID_SHAPE_SQUARE_FILL_HERMITE:
            cout << "Hermite-filled Square has been drawn\n\n";
            break;

            // ===== Rectangle =====
        case ID_SHAPE_RECT_DRAW:
            cout << "Rectangle has been drawn\n\n";
            break;
        case ID_SHAPE_RECT_FILL_BEZIER:
            cout << "Bezier-filled Rectangle has been drawn\n\n";
            break;

            // ===== Curves =====
        case ID_CURVE_HERMITE:
            cout << "Hermite Curve has been drawn\n\n";
            break;
        case ID_CURVE_BEZIER: {
            DrawBezier(hdc, points, color);
            cout << "Bezier Curve has been drawn\n\n";
            break;
        }
        case ID_CURVE_CARDINAL_SPLINE:
            cout << "Cardinal Spline Curve has been drawn\n\n";
            break;

            // ===== Fill =====
        case ID_FILL_CONVEX:
            cout << "Convex Polygon has been filled\n\n";
            break;
        case ID_FILL_NONCONVEX:
            cout << "Non-Convex Polygon has been filled\n\n";
            break;
        case ID_FILL_RECURSIVE_FF:
            cout << "Recursive Flood Fill applied\n\n";
            break;
        case ID_FILL_NONRECURSIVE_FF:
            cout << "Non-Recursive Flood Fill applied\n\n";
            break;

            // ===== Clipping =====
        case ID_CLIP_RECT_POINT:
            cout << "Point clipped in rectangle\n\n";
            break;
        case ID_CLIP_RECT_LINE:
            cout << "Line clipped in rectangle\n\n";
            break;
        case ID_CLIP_RECT_POLYGON:
            cout << "Polygon clipped in rectangle\n\n";
            break;

        case ID_CLIP_SQUARE_POINT:
            cout << "Point clipped in square\n\n";
            break;
        case ID_CLIP_SQUARE_LINE:
            cout << "Line clipped in square\n\n";
            break;

        case ID_CLIP_CIRCLE_POINT:
            cout << "Point clipped in circle\n\n";
            break;
        case ID_CLIP_CIRCLE_LINE:
            cout << "Line clipped in circle\n\n";
            break;

            // ===== Actions =====
        case ID_ACTION_CLEAR:
            cout << "Canvas cleared\n\n";
            break;
        case ID_ACTION_SAVE:
            cout << "Canvas saved\n\n";
            break;
        case ID_ACTION_LOAD:
            cout << "Canvas loaded\n\n";
            break;

            // ===== Window =====
        case ID_WINDOW_BGCOLOR:
            cout << "Background color changed\n\n";
            break;

        default:
            cout << "Unknown user choice\n\n";
            break;
    }
}
