//
// Created by sh2 on 21-May-25.
//

#ifndef PROJECT_MENUIDS_H
#define PROJECT_MENUIDS_H

//======================= Shapes ==================
//===== Line =====

#include <map>

#define ID_SHAPE_LINE_DDA            1101
#define ID_SHAPE_LINE_MIDPOINT       1102
#define ID_SHAPE_LINE_PARAM          1103

//===== Circle =====

#define ID_SHAPE_CIRCLE_DIRECT       1211
#define ID_SHAPE_CIRCLE_POLAR        1212
#define ID_SHAPE_CIRCLE_IT_POLAR     1213
#define ID_SHAPE_CIRCLE_MIDPOINT     1214
#define ID_SHAPE_CIRCLE_MOD_MIDPOINT 1215

#define ID_SHAPE_CIRCLE_FILL_LINES   1221
#define ID_SHAPE_CIRCLE_FILL_CIRCLES 1222

//===== Ellipse =====

#define ID_SHAPE_ELLIPSE_DIRECT      1301
#define ID_SHAPE_ELLIPSE_POLAR       1302
#define ID_SHAPE_ELLIPSE_MIDPOINT    1303

//===== Square =====

#define ID_SHAPE_SQUARE_DRAW         1401
#define ID_SHAPE_SQUARE_FILL_HERMITE 1402

//===== Rectangle =====

#define ID_SHAPE_RECT_DRAW           1501
#define ID_SHAPE_RECT_FILL_BEZIER    1502

//======================= CURVES =====================

#define ID_CURVE_HERMITE             2001
#define ID_CURVE_BEZIER              2002
#define ID_CURVE_CARDINAL_SPLINE     2003

//======================= Fill ===================

#define ID_FILL_CONVEX               3001
#define ID_FILL_NONCONVEX            3002
#define ID_FILL_RECURSIVE_FF         3003
#define ID_FILL_NONRECURSIVE_FF      3004

//======================= Clipping ================

//===== Rect Clip =====
#define ID_CLIP_RECT_POINT           4001
#define ID_CLIP_RECT_LINE            4002
#define ID_CLIP_RECT_POLYGON         4003

//===== Square Clip ======
#define ID_CLIP_SQUARE_POINT         4101
#define ID_CLIP_SQUARE_LINE          4102

//===== Circle clip =====
#define ID_CLIP_CIRCLE_POINT         4201
#define ID_CLIP_CIRCLE_LINE          4202

//======================= Actions ======================

#define ID_ACTION_CLEAR              5001
#define ID_ACTION_SAVE               5002
#define ID_ACTION_LOAD               5003

//======================== Window ======================

#define ID_WINDOW_BGCOLOR            6001

//===== Mouse =====
//#define ID_WINDOW_MOUSE             6100
#define ID_WINDOW_MOUSE_ARROW         6101
#define ID_WINDOW_MOUSE_HAND          6102
#define ID_WINDOW_MOUSE_CROSS         6103
#define ID_WINDOW_MOUSE_WAIT          6104
#define ID_WINDOW_MOUSE_IBEAM         6105
#define ID_WINDOW_MOUSE_SIZEALL       6106
#define ID_WINDOW_MOUSE_CUSTOM        6107

extern std::map<int, int> mapOfNeedPoints = {
        {ID_SHAPE_LINE_DDA,            2},
        {ID_SHAPE_LINE_MIDPOINT,       2},
        {ID_SHAPE_LINE_PARAM,          2},

        {ID_SHAPE_CIRCLE_DIRECT,       2},
        {ID_SHAPE_CIRCLE_POLAR,        2},
        {ID_SHAPE_CIRCLE_IT_POLAR,     2},
        {ID_SHAPE_CIRCLE_MIDPOINT,     2},
        {ID_SHAPE_CIRCLE_MOD_MIDPOINT, 2},
        {ID_SHAPE_CIRCLE_FILL_LINES,   2},
        {ID_SHAPE_CIRCLE_FILL_CIRCLES, 2},

        {ID_SHAPE_ELLIPSE_DIRECT,      2},
        {ID_SHAPE_ELLIPSE_POLAR,       2},
        {ID_SHAPE_ELLIPSE_MIDPOINT,    2},

        {ID_SHAPE_SQUARE_DRAW,         0},
        {ID_SHAPE_SQUARE_FILL_HERMITE, 0},

        {ID_SHAPE_RECT_DRAW,           0},
        {ID_SHAPE_RECT_FILL_BEZIER,    0},

        {ID_CURVE_HERMITE,             0},
        {ID_CURVE_BEZIER,              4},
        {ID_CURVE_CARDINAL_SPLINE,     0},

        {ID_FILL_CONVEX,               1},
        {ID_FILL_NONCONVEX,            1},
        {ID_FILL_RECURSIVE_FF,         1},
        {ID_FILL_NONRECURSIVE_FF,      1},

        {ID_CLIP_RECT_POINT,           0},
        {ID_CLIP_RECT_LINE,            0},
        {ID_CLIP_RECT_POLYGON,         0},

        {ID_CLIP_SQUARE_POINT,         0},
        {ID_CLIP_SQUARE_LINE,          0},

        {ID_CLIP_CIRCLE_POINT,         0},
        {ID_CLIP_CIRCLE_LINE,          0},

        {ID_WINDOW_MOUSE_ARROW,        -1},
        {ID_WINDOW_MOUSE_HAND,         -1},
        {ID_WINDOW_MOUSE_CROSS,        -1},
        {ID_WINDOW_MOUSE_WAIT,         -1},
        {ID_WINDOW_MOUSE_IBEAM,        -1},
        {ID_WINDOW_MOUSE_SIZEALL,      -1},
        {ID_WINDOW_MOUSE_CUSTOM,       -1}
};

#endif //PROJECT_MENUIDS_H
