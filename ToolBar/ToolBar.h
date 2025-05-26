#ifndef PROJECT_TOOLBAR_H
#define PROJECT_TOOLBAR_H

#include <tchar.h>
#include <windows.h>
#include "MenuIDs.h"

void createToolBar(HWND hwnd) {
    HMENU hMenu = CreateMenu();

    // ============= Action Menu ==========
    HMENU actionMenu = CreatePopupMenu();
    AppendMenu(actionMenu, MF_STRING, ID_ACTION_CLEAR, "Clear");
    AppendMenu(actionMenu, MF_STRING, ID_ACTION_SAVE, "Save");
    AppendMenu(actionMenu, MF_STRING, ID_ACTION_LOAD, "Load");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) actionMenu, "File");

    // ============= Window Menu ==========
    HMENU windowMenu = CreatePopupMenu();
    AppendMenu(windowMenu, MF_STRING, ID_WINDOW_BGCOLOR, "Change Background Color");
    AppendMenu(windowMenu, MF_STRING, ID_WINDOW_MOUSE, "Change Mouse Shape");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) windowMenu, "Window");

    // ============= Shapes Menu ==========
    HMENU shapeMenu = CreatePopupMenu();

    // ----- Line Submenu -----
    HMENU lineMenu = CreatePopupMenu();
    AppendMenu(lineMenu, MF_STRING, ID_SHAPE_LINE_DDA, "Line - DDA");
    AppendMenu(lineMenu, MF_STRING, ID_SHAPE_LINE_MIDPOINT, "Line - Midpoint");
    AppendMenu(lineMenu, MF_STRING, ID_SHAPE_LINE_PARAM, "Line - Parametric");

    AppendMenu(shapeMenu, MF_POPUP, (UINT_PTR) lineMenu, "Line");

    // ----- Circle Submenu -----
    HMENU circleMenu = CreatePopupMenu();

    // Circle Draw
    HMENU circleDrawMenu = CreatePopupMenu();
    AppendMenu(circleDrawMenu, MF_STRING, ID_SHAPE_CIRCLE_DIRECT, "Circle - Direct");
    AppendMenu(circleDrawMenu, MF_STRING, ID_SHAPE_CIRCLE_POLAR, "Circle - Polar");
    AppendMenu(circleDrawMenu, MF_STRING, ID_SHAPE_CIRCLE_IT_POLAR, "Circle - Iterative Polar");
    AppendMenu(circleDrawMenu, MF_STRING, ID_SHAPE_CIRCLE_MIDPOINT, "Circle - Midpoint");
    AppendMenu(circleDrawMenu, MF_STRING, ID_SHAPE_CIRCLE_MOD_MIDPOINT, "Circle - Modified MidPoint");

    AppendMenu(circleMenu, MF_POPUP, (UINT_PTR) circleDrawMenu, "Draw Circle");

    //Circle Fill
    HMENU circleFillMenu = CreatePopupMenu();
    AppendMenu(circleFillMenu, MF_STRING, ID_SHAPE_CIRCLE_FILL_LINES, "Fill Circle with Lines");
    AppendMenu(circleFillMenu, MF_STRING, ID_SHAPE_CIRCLE_FILL_CIRCLES, "Fill Circle with Circles");

    AppendMenu(circleMenu, MF_POPUP, (UINT_PTR) circleFillMenu, "Fill Circle");

    //
    AppendMenu(shapeMenu, MF_POPUP, (UINT_PTR) circleMenu, "Circle");


    // ----- Ellipse Submenu -----
    HMENU ellipseMenu = CreatePopupMenu();
    AppendMenu(ellipseMenu, MF_STRING, ID_SHAPE_ELLIPSE_DIRECT, "Ellipse - Direct");
    AppendMenu(ellipseMenu, MF_STRING, ID_SHAPE_ELLIPSE_POLAR, "Ellipse - Polar");
    AppendMenu(ellipseMenu, MF_STRING, ID_SHAPE_ELLIPSE_MIDPOINT, "Ellipse - Midpoint");

    AppendMenu(shapeMenu, MF_POPUP, (UINT_PTR) ellipseMenu, "Ellipse");

    // ----- Square Submenu -----
    HMENU squareMenu = CreatePopupMenu();
    AppendMenu(squareMenu, MF_STRING, ID_SHAPE_SQUARE_DRAW, "Draw Square");
    AppendMenu(squareMenu, MF_STRING, ID_SHAPE_SQUARE_FILL_HERMITE, "Fill Square with Hermite");

    AppendMenu(shapeMenu, MF_POPUP, (UINT_PTR) squareMenu, "Square");

    // ----- Rectangle Submenu -----
    HMENU rectangleMenu = CreatePopupMenu();
    AppendMenu(rectangleMenu, MF_STRING, ID_SHAPE_RECT_DRAW, "Draw Rectangle");
    AppendMenu(rectangleMenu, MF_STRING, ID_SHAPE_RECT_FILL_BEZIER, "Fill Rectangle with Bezier");
    AppendMenu(shapeMenu, MF_POPUP, (UINT_PTR) rectangleMenu, "Rectangle");

    // Add the whole Shapes Menu
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) shapeMenu, "Shapes");

    // ============= Curve Menu ==========
    HMENU curveMenu = CreatePopupMenu();
    AppendMenu(curveMenu, MF_STRING, ID_CURVE_HERMITE, "Curve - Hermite");
    AppendMenu(curveMenu, MF_STRING, ID_CURVE_BEZIER, "Curve - Bezier");
    AppendMenu(curveMenu, MF_STRING, ID_CURVE_CARDINAL_SPLINE, "Curve - Cardinal");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) curveMenu, "Curves");

    // ============= Fill Menu ==========
    HMENU fillMenu = CreatePopupMenu();
    AppendMenu(fillMenu, MF_STRING, ID_FILL_CONVEX, "Fill - Convex Polygon");
    AppendMenu(fillMenu, MF_STRING, ID_FILL_NONCONVEX, "Fill - Non-Convex Polygon");
    AppendMenu(fillMenu, MF_STRING, ID_FILL_RECURSIVE_FF, "Fill - Flood Fill (Recursive)");
    AppendMenu(fillMenu, MF_STRING, ID_FILL_NONRECURSIVE_FF, "Fill - Flood Fill (Non-Recursive)");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) fillMenu, "Fill");

    // ============= Clipping Menu ==========
    HMENU clipMenu = CreatePopupMenu();

    // ----- Rectangle Clip Submenu -----
    HMENU rectangleClipMenu = CreatePopupMenu();
    AppendMenu(rectangleClipMenu, MF_STRING, ID_CLIP_RECT_POINT, "Rectangle Clipping - Point");
    AppendMenu(rectangleClipMenu, MF_STRING, ID_CLIP_RECT_LINE, "Rectangle Clipping - Line");
    AppendMenu(rectangleClipMenu, MF_STRING, ID_CLIP_RECT_POLYGON, "Rectangle Clipping - POLYGON");

    AppendMenu(clipMenu, MF_POPUP, (UINT_PTR) rectangleClipMenu, "Rectangle Clipping");

    // ----- Square Clip Submenu -----
    HMENU squareClipMenu = CreatePopupMenu();
    AppendMenu(squareClipMenu, MF_STRING, ID_CLIP_SQUARE_POINT, "Square Clipping - Point");
    AppendMenu(squareClipMenu, MF_STRING, ID_CLIP_SQUARE_LINE, "Square Clipping - Line");

    AppendMenu(clipMenu, MF_POPUP, (UINT_PTR) squareClipMenu, "Square Clipping");

    // ----- Circle Clip Submenu -----
    HMENU circleClipMenu = CreatePopupMenu();
    AppendMenu(circleClipMenu, MF_STRING, ID_CLIP_CIRCLE_POINT, "Circle Clipping - Point");
    AppendMenu(circleClipMenu, MF_STRING, ID_CLIP_CIRCLE_LINE, "Circle Clipping - Line");

    AppendMenu(clipMenu, MF_POPUP, (UINT_PTR) circleClipMenu, "Circle Clipping");

    // Add the whole Shapes Menu
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) clipMenu, "Clipping");

    // ===== Attach to Window =====
    SetMenu(hwnd, hMenu);
}

#endif //PROJECT_TOOLBAR_H
