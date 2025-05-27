//
// Created by sh2 on 27-May-25.
//

#ifndef PROJECT_CURSORCHANGER_H
#define PROJECT_CURSORCHANGER_H

#include <windows.h>
#include<iostream>
#include <vector>
#include "MenuIDs.h"

using namespace std;

void customCursorMenu() {
    cout << "Custom Cursor Menu :)\n";
    cout << "1: Clown\n";
    cout << "2: Cat Paw\n";
    cout << "3: Goose\n";
    cout << "4: Tom\n";
    cout << "5: Smile\n";
    cout << "6: Just a Ribbon\n";
    cout << "Choose a Custom Cursor:\n";
}

HCURSOR changeCursor(int userChoice) {
    static std::vector<LPCSTR> cursors = {
            IDC_ARROW, IDC_HAND, IDC_CROSS, IDC_WAIT, IDC_IBEAM, IDC_SIZEALL
    };

    static std::vector<LPCSTR> customCursorPaths = {
            "Files/Cursors/cursor.cur",
            "Files/Cursors/cat.cur",
            "Files/Cursors/goose.cur",
            "Files/Cursors/tom.cur",
            "Files/Cursors/smile.cur",
            "Files/Cursors/ribbon.cur",
    };

    if (userChoice != ID_WINDOW_MOUSE_CUSTOM) {
        int index = userChoice - ID_WINDOW_MOUSE_ARROW;
        return LoadCursor(NULL, cursors[index]);
    }

    customCursorMenu();
    int choice;
    cin >> choice;
    if (cin.fail() || choice < 1 || choice > customCursorPaths.size()) {
        cout << "Invalid Option\n";
        return NULL;
    }

    string projectPath = "../";
    string fullPath = projectPath + customCursorPaths[choice - 1];
    HCURSOR cursor = LoadCursorFromFile(fullPath.c_str());
    if (!cursor) {
        cout << "Failed to load cursor file: " << customCursorPaths[choice - 1] << "\n";
        cout << "Error Code: " << GetLastError() << "\n";

        char fullPath[MAX_PATH];
        GetFullPathName(customCursorPaths[choice - 1], MAX_PATH, fullPath, NULL);
        cout << "Trying to load cursor from: " << fullPath << "\n";

    }
    return cursor;
}

#endif //PROJECT_CURSORCHANGER_H
