//
// Created by sh2 on 21-May-25.
//

#ifndef PROJECT_DRAW_H
#define PROJECT_DRAW_H

#include <windows.h>
#include "MenuIDs.h"


void draw(WPARAM wParam, HWND hwnd, HDC hdc) {
    switch (LOWORD(wParam)) {
        case ID_SHAPE_LINE_DDA:
            //currentMode = DRAW_LINE_DDA;
            break;
        case ID_ACTION_CLEAR:
            //shapes.clear();
            InvalidateRect(hwnd, nullptr, TRUE);
            break;
        case ID_ACTION_SAVE:
            //SaveShapes("shapes.txt");
            break;
        case ID_ACTION_LOAD:
            //LoadShapes("shapes.txt");
            InvalidateRect(hwnd, nullptr, TRUE);
            break;
            // Add more handlers...
    }
}

#endif //PROJECT_DRAW_H
