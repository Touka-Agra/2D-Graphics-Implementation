#ifndef PROJECT_Draw_H
#define PROJECT_Draw_H


#include <windows.h>
#include <iostream>
#include <vector>
#include "MenuIDs.h"
#include "../Classes/Point.h"
#include "../Classes/Paint.h"
#include "../Curves/Bezier.h"
#include "../Curves/CardinalSplineCurve.h"
#include "../Shapes/Line/DDALine.h"
#include "../Shapes/Line/BresenhamLine.h"
#include "../Shapes/Line/InterpolatedLine.h"
#include "../Shapes/Circle/CircleDirect.h"
#include "../Shapes/Circle/CirclePolar.h"
#include "../Shapes/Circle/CircleModifiedMidpoint.h"
#include "../Shapes/Circle/CircleMidpoint.h"
#include "../Shapes/Circle/CircleIterativePolar.h"
#include "../Shapes/Circle/FillCircleWithCircles.h"
#include "../Shapes/Circle/FillCircleWithLines.h"
#include "../Clipping/Rectangle&Square/PointClipping.h"
#include "../Clipping/Rectangle&Square/LineClipping.h"
#include "../Clipping/Rectangle&Square/PolygonClipping.h"
#include "../Utilities/fileUtilitis.h"
#include "../Filling/ConvexFill.h"
#include "../Filling/GeneralPolygonFill.h"
#include "../Filling/recursiveFloodFill.h"
#include "../Filling/iterativeFloodFill.h"
#include "../Shapes/Ellipse/standardEllipse.h"
#include "../Shapes/Ellipse/polarEllipse.h"
#include "../Shapes/Ellipse/MidpointEllipse.h"
#include "../Clipping/Circle/PointClip.h"
#include "../Clipping/Circle/LineClip.h"
#include "../Filling/FillingWithHermit Curve.h"
#include "../Filling/FillingWithBezierCurve.h"
#include "../Shapes/Rectangle/Rectangle.h"
#include "../Shapes/Square/Square.h"



using namespace std;

vector<Paint> paints = {};

void draw(HWND hwnd, HDC hdc, int userChoice, vector<Point> points, COLORREF color) {
    bool updatePaints = true;
    switch (userChoice) {
        case ID_PIXEL:
            SetPixel(hdc, points[0].x, points[0].y, color);
            cout << "Pixel has been drawn\n\n";
            break;
            // ===== Line =====
        case ID_SHAPE_LINE_DDA:
            drawDDALine(hdc, points, color);
            cout << "DDA Line has been drawn\n\n";
            break;
        case ID_SHAPE_LINE_MIDPOINT:
            cout << color << endl;
            drawBresenhamLine(hdc, points, color);
            cout << "Midpoint Line has been drawn\n\n";
            break;
        case ID_SHAPE_LINE_PARAM:
            drawParametricLine(hdc, points, color);
            cout << "Parametric Line has been drawn\n\n";
            break;

            // ===== Circle =====
        case ID_SHAPE_CIRCLE_DIRECT:
            drawCircleDirect(hdc, points, color);
            cout << "Direct Circle has been drawn\n\n";
            break;
        case ID_SHAPE_CIRCLE_POLAR:
            drawCirclePolar(hdc, points, color);
            cout << "Polar Circle has been drawn\n\n";
            break;
        case ID_SHAPE_CIRCLE_IT_POLAR:
            drawCircleIterativePolar(hdc, points, color);
            cout << "Iterative Polar Circle has been drawn\n\n";
            break;
        case ID_SHAPE_CIRCLE_MIDPOINT:
            drawCircleMidpoint(hdc, points, color);
            cout << "Midpoint Circle has been drawn\n\n";
            break;
        case ID_SHAPE_CIRCLE_MOD_MIDPOINT:
            drawCircleModifiedMidpoint(hdc, points, color);
            cout << "Modified Midpoint Circle has been drawn\n\n";
            break;
        case ID_SHAPE_CIRCLE_FILL_LINES:
            fillQuarterCircleWithLines(hdc, points, color);
            cout << "Filled Circle with Lines has been drawn\n\n";
            break;
        case ID_SHAPE_CIRCLE_FILL_CIRCLES:
            fillQuarterCircleWithCircles(hdc, points, color);
            cout << "Filled Circle with Circles has been drawn\n\n";
            break;

            // ===== Ellipse =====
        case ID_SHAPE_ELLIPSE_DIRECT:
            DrawEllipse(hdc, points, color);
            cout << "Direct Ellipse has been drawn\n\n";
            break;
        case ID_SHAPE_ELLIPSE_POLAR:
            DrawPolarEllipse(hdc,points,color);
            cout << "Polar Ellipse has been drawn\n\n";
            break;
        case ID_SHAPE_ELLIPSE_MIDPOINT:
            DrawMidpointEllipse(hdc,points,color);
            cout << "Midpoint Ellipse has been drawn\n\n";
            break;

            // ===== Square =====
        case ID_SHAPE_SQUARE_DRAW:
            DrawSquare(hdc, points, color);
            cout << "Square has been drawn\n\n";
            break;
        case ID_SHAPE_SQUARE_FILL_HERMITE:
            FillSquareWithHermiteCurve(hdc, points, color);
            cout << "Hermite-filled Square has been drawn\n\n";
            break;

            // ===== Rectangle =====
        case ID_SHAPE_RECT_DRAW:
            DrawRectangle(hdc, points, color);
            cout << "Rectangle has been drawn\n\n";
            break;
        case ID_SHAPE_RECT_FILL_BEZIER:
            FillRectangleWithBezierCurve(hdc, points, color);
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
            DrawCardinalSpline(hdc, points, 0.5, color);
            DrawControlPoints(hdc, points, RGB(255, 0, 0));
            cout << "Cardinal Spline Curve has been drawn\n\n";
            break;

            // ===== Fill =====
        case ID_FILL_CONVEX:
            ConvexFill(hdc, points, color);
            cout << "Convex Polygon has been filled\n\n";
            break;
        case ID_FILL_NONCONVEX:
            GeneralPolygonFill(hdc, points, color);
            cout << "Non-Convex Polygon has been filled\n\n";
            break;
        case ID_FILL_RECURSIVE_FF: {
            COLORREF bgColor = GetPixel(hdc, points[0].x, points[0].y);
            recursiveFloodFill(hdc, points[0].x, points[0].y, color, bgColor);
            cout << "Recursive Flood Fill applied\n\n";
        }
            break;
        case ID_FILL_NONRECURSIVE_FF: {
            COLORREF bgColor = GetPixel(hdc, points[0].x, points[0].y);
            iterativeFloodFill(hdc, points[0].x, points[0].y, color, bgColor);
            cout << "Non-Recursive Flood Fill applied\n\n";
        }
            break;

            // ===== Actions =====
        case ID_ACTION_CLEAR:
            clearFile(hwnd, paints);
            cout << "Canvas cleared\n\n";
            updatePaints = false;
            break;

        case ID_ACTION_SAVE: {
            string chosenFile = getChosenFile();
            bool isSaved = saveFile(chosenFile, paints, true);
            if(isSaved) cout << "Canvas saved\n\n";
            updatePaints = false;
            break;
        }

        case ID_ACTION_LOAD: {
            string chosenFile = getChosenFile();
            bool isLoaded = loadFile(hwnd, hdc, chosenFile, paints);
            if(isLoaded) cout << "Canvas loaded\n\n";
            updatePaints = false;
            break;
        }

        default:
            cout << "Unknown user choice\n\n";
            break;
    }

    if (updatePaints) {
        Paint paint = Paint(userChoice, points, color);
        paints.push_back(paint);
    }

}

void clip(HDC hdc, int userChoice, vector<Point> points, vector<int> window, COLORREF color) {
    switch (userChoice) {
        // ===== Clipping =====
        case ID_CLIP_RECT_POINT: {
            bool drawPoint = drawClippedPoint(hdc, points, window, color);
            if (drawPoint) {
                Paint paint = Paint(ID_PIXEL, points, color);
                paints.push_back(paint);
            }
            cout << "Point clipped in rectangle\n\n";
            break;
        }
        case ID_CLIP_RECT_LINE: {
            Paint paint = drawClippedLine(hdc, points, window, color);
            if (paint.getType() != 0) paints.push_back(paint);
            cout << "Line clipped in rectangle\n\n";
            break;
        }
        case ID_CLIP_RECT_POLYGON: {
            vector<Paint> polygon = drawClippedPolygon(hdc, points, window, color);
            cout << "Polygon clipped in rectangle\n\n";
            paints.insert(paints.end(), polygon.begin(), polygon.end());
            break;
        }
        case ID_CLIP_SQUARE_POINT: {
            bool drawPoint = drawClippedPoint(hdc, points, window, color);
            if (drawPoint) {
                Paint paint = Paint(ID_PIXEL, points, color);
                paints.push_back(paint);
            }
            cout << "Point clipped in square\n\n";
            break;
        }
        case ID_CLIP_SQUARE_LINE: {
            Paint paint = drawClippedLine(hdc, points, window, color);
            if (paint.getType() != 0) paints.push_back(paint);
            cout << "Line clipped in square\n\n";
            break;
        }
        case ID_CLIP_CIRCLE_POINT: {
            bool drawPoint = drawClippedPointC(hdc, points, window, color);
            if (drawPoint) {
                Paint paint = Paint(ID_PIXEL, points, color);
                paints.push_back(paint);
            }
            cout << "Point clipped in circle\n\n";
            break;
        }
        case ID_CLIP_CIRCLE_LINE: {
            Paint paint = drawClippedLineC(hdc, points, window, color);
            if (paint.getType() != 0) paints.push_back(paint);
            cout << "Line clipped in circle\n\n";
            break;
        }
    }
}
#endif