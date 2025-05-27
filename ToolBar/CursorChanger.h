//
// Created by sh2 on 27-May-25.
//

#ifndef PROJECT_CURSORCHANGER_H
#define PROJECT_CURSORCHANGER_H

#include <windows.h>
#include <vector>
#include "MenuIDs.h"

HCURSOR changeCursor(int userChoice) {
    static std::vector <LPCSTR> cursors = {
            IDC_ARROW, IDC_HAND, IDC_CROSS, IDC_WAIT, IDC_IBEAM, IDC_SIZEALL
    };

    if(userChoice != ID_WINDOW_MOUSE_CUSTOM){
        int index = userChoice - ID_WINDOW_MOUSE_ARROW;
        cout << "Mouse cursor changed\n\n";
        return LoadCursor(NULL, cursors[index]);
    }
    else{
        cout << "Mouse cursor changed\n\n";
        return LoadCursorFromFile("cursor.cur");
    }
}

#endif //PROJECT_CURSORCHANGER_H
