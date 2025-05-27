//
// Created by sh2 on 27-May-25.
//

#ifndef PROJECT_COLORPICKER_H
#define PROJECT_COLORPICKER_H

#include <windows.h>

COLORREF pickColor(HWND hwnd, COLORREF color){
    CHOOSECOLOR cc;
    static COLORREF customColors[16];

    ZeroMemory(&cc, sizeof(cc));
    cc.lStructSize = sizeof(cc);

    cc.hwndOwner = hwnd;
    cc.lpCustColors = customColors;
    cc.rgbResult = color;
    cc.Flags = CC_FULLOPEN | CC_RGBINIT;

    if (ChooseColor(&cc)) {
        color = cc.rgbResult;
    }

    return color;

}
#endif //PROJECT_COLORPICKER_H
