#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <vector>
#include "ToolBar/ToolBar.h"
#include "ToolBar/MenuIDs.h"
#include "ToolBar/Draw.h"
#include "ToolBar/ColorPicker.h"
#include "ToolBar/CursorChanger.h"
#include "Classes/Point.h"

using namespace std;


//Window Background Color
COLORREF chosenBgColor = RGB(50, 100,150);
HBRUSH brush =  CreateSolidBrush(chosenBgColor);

bool myloadFile(HDC hdc, string filename) {
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
        cout << colorS << endl;
        COLORREF color = (COLORREF) colorS;

        cout << type << " " << numOfPoints << color << endl;

        draw(hdc, type, points, color);
    }

    cout << "All are loaded\n";

    return true;
}


/* Function declarations */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK OverlayProc(HWND, UINT, WPARAM, LPARAM);

/* Global variables */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

HDC hdc;
vector<Point> points;
vector<int> window;

int userChoice;
int needPoints;

COLORREF chosenColor = RGB(255, 0, 0);
HCURSOR chosenCursor = LoadCursor(NULL, IDC_ARROW);

RECT clipRect;    // Rectangle clipping area
RECT clipSqu;     // Square clipping area
int margin = 50;
HWND hOverlay = NULL;

void UpdateOverlayPosition(HWND hwndParent) {
    if (hOverlay == NULL) return;

    RECT rc;
    GetClientRect(hwndParent, &rc);

    POINT topLeft = {rc.left + margin, rc.top + margin};
    ClientToScreen(hwndParent, &topLeft);

    int width = (rc.right - rc.left) - 2 * margin;
    int height = (rc.bottom - rc.top) - 2 * margin;

    SetWindowPos(hOverlay, HWND_TOP, topLeft.x, topLeft.y, width, height, SWP_NOACTIVATE | SWP_NOZORDER);
}

void ShowClippingOverlay(HWND hwndParent) {
    if (hOverlay != NULL) return;

    hOverlay = CreateWindowEx(
            WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW,
            _T("OverlayWindowClass"), NULL,
            WS_POPUP,
            0, 0, 0, 0, // will be resized immediately
            hwndParent, NULL, GetModuleHandle(NULL), NULL);

    SetWindowLong(hOverlay, GWL_EXSTYLE,
                  GetWindowLong(hOverlay, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);

    SetLayeredWindowAttributes(hOverlay, RGB(0, 0, 0), 0, LWA_COLORKEY);

    ShowWindow(hOverlay, SW_SHOW);
    UpdateOverlayPosition(hwndParent);
}

void HideClippingOverlay() {
    if (hOverlay) {
        DestroyWindow(hOverlay);
        hOverlay = NULL;
    }
}

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    cout << "Console initialized" << endl;
    Sleep(2000);

    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = brush;

    if (!RegisterClassEx(&wincl)) return 0;

    // Register overlay class
    WNDCLASS overlayClass = {};
    overlayClass.lpfnWndProc = OverlayProc;
    overlayClass.hInstance = hThisInstance;
    overlayClass.lpszClassName = _T("OverlayWindowClass");
    overlayClass.hbrBackground = (HBRUSH) GetStockObject(NULL_BRUSH);
    overlayClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    overlayClass.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&overlayClass);

    hwnd = CreateWindowEx(
            0,
            szClassName,
            "Fixed Size Window",
            WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, // No maximize or resize
            CW_USEDEFAULT, CW_USEDEFAULT,
            800, 600,  // Fixed width and height
            NULL,
            NULL,
            hThisInstance,
            NULL
    );

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&messages, NULL, 0, 0)) {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_LBUTTONDOWN: {
            double x = LOWORD(lParam);
            double y = HIWORD(lParam);

            if (userChoice != NULL) {
                Point point = Point(x, y);
                points.push_back(point);

                if (points.size() == needPoints) {
                    std::cout << "Draw function called with " << points.size() << " points\n";

                    hdc = GetDC(hwnd);
                    if (userChoice >= ID_CLIP_RECT_POINT && userChoice <= ID_CLIP_CIRCLE_LINE) {
                        clip(hdc, userChoice, points, window, chosenColor);
                    } else {
                        draw(hdc, userChoice, points, chosenColor);
                    }

                    ReleaseDC(hwnd, hdc);
                    points.clear();
                }
            } else {
                cout << "Unknown User Choice\n\n";
            }
            break;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
            break;
        }

        case WM_MOVE:
        case WM_SIZE:
            UpdateOverlayPosition(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_CREATE:
            createToolBar(hwnd);
            break;

        case WM_COMMAND:
            points.clear();
            userChoice = LOWORD(wParam);
            cout << "User Choice: " << userChoice << endl;
            needPoints = mapOfNeedPoints[userChoice];

            if(userChoice == ID_ACTION_LOAD){
            hdc = GetDC(hwnd);
            myloadFile(hdc, "../Files/SavedFiles/test.txt");
            ReleaseDC(hwnd, hdc);
            }
            else {
                if (needPoints != -1) {
                    chosenColor = pickColor(hwnd, chosenColor);
                }

                if (userChoice == ID_CLIP_RECT_POINT || userChoice == ID_CLIP_RECT_LINE ||
                    userChoice == ID_CLIP_RECT_POLYGON) {
                    // Rectangle Clipping
                    ShowClippingOverlay(hwnd);

                    RECT client;
                    GetClientRect(hwnd, &client);

                    // Rectangle is the full client area minus the margin
                    clipRect.left = client.left + margin;
                    clipRect.right = client.right - margin;
                    clipRect.top = client.top + margin;
                    clipRect.bottom = client.bottom - margin;

                    cout << "Rectangle clipRect: Left=" << clipRect.left
                         << ", Top=" << clipRect.top
                         << ", Right=" << clipRect.right
                         << ", Bottom=" << clipRect.bottom
                         << ", Size=" << clipRect.right - clipRect.left << "x" << clipRect.bottom - clipRect.top
                         << endl;

                    // Clear the window vector and store rectangle coordinates
                    window.clear();
                    window.push_back(clipRect.left);
                    window.push_back(clipRect.right);
                    window.push_back(clipRect.top);
                    window.push_back(clipRect.bottom);
                }
                else if (userChoice == ID_CLIP_SQUARE_POINT || userChoice == ID_CLIP_SQUARE_LINE) {
                    // Square Clipping
                    ShowClippingOverlay(hwnd);

                    RECT client;
                    GetClientRect(hwnd, &client);

                    int clientWidth = client.right - client.left - 2 * margin;
                    int clientHeight = client.bottom - client.top - 2 * margin;

                    // Use the smallest dimension to create a square
                    int squareSize = min(clientWidth, clientHeight);

                    // Center the square in the client area
                    int left = (client.right + client.left - squareSize) / 2;
                    int top = (client.bottom + client.top - squareSize) / 2;

                    // Set the clipRect to represent the square
                    clipSqu.left = left;
                    clipSqu.top = top;
                    clipSqu.right = left + squareSize;
                    clipSqu.bottom = top + squareSize;

                    cout << "Square clipRect: Left=" << clipSqu.left
                         << ", Top=" << clipSqu.top
                         << ", Right=" << clipSqu.right
                         << ", Bottom=" << clipSqu.bottom
                         << ", Size=" << clipSqu.right - clipSqu.left << "x" << clipSqu.bottom - clipSqu.top << endl;

                    // Clear the window vector and store square coordinates
                    window.clear();
                    window.push_back(clipSqu.left);
                    window.push_back(clipSqu.right);
                    window.push_back(clipSqu.top);
                    window.push_back(clipSqu.bottom);
                } else {
                    // Hide clipping overlay if not rectangle or square
                    HideClippingOverlay();
                    window.clear();
                }

                if (userChoice >= ID_WINDOW_MOUSE_ARROW && userChoice <= ID_WINDOW_MOUSE_CUSTOM) {
                    // Handle cursor change
                    chosenCursor = changeCursor(userChoice);
                    cout << "Mouse cursor changed\n\n";
                }
                else if (userChoice == ID_WINDOW_BGCOLOR) {
                    DeleteObject(brush);
                    chosenBgColor = pickColor(hwnd, chosenBgColor);
                    brush = CreateSolidBrush(chosenBgColor);
                    InvalidateRect(hwnd, NULL, false); // Force redraw
                }
                else if (needPoints <= 0) {
                    // Perform drawing if needed
                    hdc = GetDC(hwnd);
                    if (userChoice == ID_CLIP_RECT_POLYGON || userChoice == ID_FILL_CONVEX ||  userChoice == ID_FILL_NONCONVEX) {
                        int numPts;
                        cout << "Enter number of points: ";
                        cin >> numPts;
                        needPoints = numPts;
                    } else {
                        draw(hdc, userChoice, points, chosenColor);
                    }
                    ReleaseDC(hwnd, hdc);
                }
            }
            break;

        case WM_SETCURSOR:
            if (chosenCursor != NULL) {
                SetCursor(chosenCursor);
            }
            break;

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK OverlayProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            HPEN hPen = CreatePen(PS_DASH, 1, RGB(255, 0, 0));  // Red Pen for Rectangle
            HPEN hOldPen = (HPEN) SelectObject(hdc, hPen);
            HBRUSH hOldBrush = (HBRUSH) SelectObject(hdc, GetStockObject(NULL_BRUSH));

            // Rectangle clipping area
            RECT rc = clipRect;
            rc.left -= margin;
            rc.right -= margin;
            rc.top -= margin;
            rc.bottom -= margin;

            Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

            // Square clipping area
            RECT sq = clipSqu;
            sq.left -= margin;
            sq.right -= margin;
            sq.top -= margin;
            sq.bottom -= margin;

            Rectangle(hdc, sq.left, sq.top, sq.right, sq.bottom);

            SelectObject(hdc, hOldPen);
            SelectObject(hdc, hOldBrush);
            DeleteObject(hPen);

            EndPaint(hwnd, &ps);
            return 0;
        }

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}