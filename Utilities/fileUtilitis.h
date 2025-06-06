//
// Created by sh2 on 01-Jun-25.
//

#ifndef PROJECT_FILEUTILITIS_H
#define PROJECT_FILEUTILITIS_H

#include <iostream>
#include<fstream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include "../Classes/Paint.h"
#include "../ToolBar/Draw.h"

using namespace std;

vector<string> savedFiles = {};

string getChosenFile() {
    string filename = "../Files/SavedFiles/master";
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << "Something went wrong :(\n";
        return "-1";
    }

    savedFiles.clear();
    cout << "\nFiles:\n";
    string line;
    int counter = 1;
    while (inFile >> line) {
        cout << counter << ": " << line << endl;
        savedFiles.push_back(line);
        counter++;
    }
    if (savedFiles.empty()) cout << "No Files exist.";
    cout << endl;

    cout << "Enter a filename or path:";
    string chosenFile;
    cin >> chosenFile;
    cout << endl;

    if (chosenFile.find(".txt") == string::npos) {
        chosenFile.append(".txt");
    }

    bool isPath = (chosenFile.find('/') != string::npos || chosenFile.find('\\') != string::npos);
    if (!isPath) {
        chosenFile = "../Files/SavedFiles/" + chosenFile;
    }

    return chosenFile;
}

bool saveFile(string chosenFile, vector<Paint> paints, bool isUser) {
    bool isNewFile = (find(savedFiles.begin(), savedFiles.end(), chosenFile) == savedFiles.end());

    ofstream outFile(chosenFile);

    if (isUser && !isNewFile) {
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

    if (!outFile.is_open()) {
        cout << "Save Error: Couldn't open the File\n";
        return false;
    }

    if (isNewFile) {
        savedFiles.push_back(chosenFile);
        ofstream masterOut("../Files/SavedFiles/master", ios::app);
        if (masterOut.is_open()) {
            masterOut << chosenFile << "\n";
            masterOut.close();
            cout << "New file is added.\n";
        } else {
            cout << "Warning: Couldn't update master file.\n";
            return false;
        }
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
    outFile.close();
    return true;
}

void clearFile(HWND hwnd, vector<Paint> &paints) {
    paints.clear();

    InvalidateRect(hwnd, NULL, TRUE);
    UpdateWindow(hwnd);
    return;
}

void draw(HWND hwnd, HDC hdc, int userChoice, vector<Point> points, COLORREF color);

bool loadFile(HWND hwnd, HDC hdc, string chosenFile, vector<Paint> &paints) {
    clearFile(hwnd, paints);
    ifstream inFile(chosenFile);

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
    inFile.close();
    return true;
}

#endif //PROJECT_FILEUTILITIS_H
