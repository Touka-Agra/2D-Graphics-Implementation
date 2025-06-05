//
// Created by sh2 on 01-Jun-25.
//

#ifndef PROJECT_FILEUTILITIS_H
#define PROJECT_FILEUTILITIS_H

#include <iostream>
#include<fstream>
#include <windows.h>
#include <vector>
#include "../Classes/Paint.h"
#include "../ToolBar/Draw.h"

using namespace std;

bool saveFile(const string filename, vector<Paint> paints, bool isUser) {

    ofstream outFile(filename);

    if (isUser) {
        if (outFile.good()) {
            cout << "File already exists.\n";

            again:;
            cout << "You want to override? y/n: ";
            string choice;
            cin >> choice;

            if (choice == "n") {
                cout << "Saving File stopped.\n";
                return false;
            } else if (choice != "y") {
                cout << "Invalid Choice! try again.\n";
                goto again;
            }
            cout << endl;
        }
    }

    if (!outFile.is_open()) {
        cout << "Save Error: Couldn't open the File\n";
        return false;
    }

    for (Paint paint: paints) {
        outFile << paint.getType() << " " << paint.getNumOfPoints() << " ";
        vector<Point> points = paint.getPoints();
        for (int i = 0; i < points.size(); i++) {
            Point p = points[i];
            outFile << p.x << " " << p.y << " ";
        }
        outFile << paint.getColor() << "\n";
    }
    return true;
}

void clearFile(HWND hwnd ,vector<Paint> &paints) {
    paints.clear();

    InvalidateRect(hwnd, NULL, TRUE);
    UpdateWindow(hwnd);
    return;
}

void draw(HWND hwnd, HDC hdc, int userChoice, vector<Point> points, COLORREF color);

bool loadFile(HWND hwnd, HDC hdc ,string filename, vector<Paint> paints) {
    clearFile(hwnd, paints);
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << "Load Error: Couldn't open the File\n";
        return false;
    }

    string typeS;
    while (inFile >> typeS) {
        int type = stoi(typeS);
        vector<Point> points;

        string numOfPointsS;
        inFile >> numOfPointsS;
        int numOfPoints = stoi(numOfPointsS);

        for (int i = 0; i < numOfPoints; i++) {
            double x, y;
            inFile >> x >> y;
            Point point = Point(x, y);

            points.push_back(point);
        }

        unsigned long colorS;
        inFile >> colorS;
        COLORREF color = (COLORREF) colorS;

        draw(hwnd, hdc, type, points, color);
    }

    cout << "All are loaded\n";

    return true;
}

#endif //PROJECT_FILEUTILITIS_H
