#include <Windows.h>
#include <algorithm>
#include <cmath>

using namespace std;

int Round(double x)
{
    return (int)(x + 0.5);
}

void draw4Points(HDC hdc, int centerX, int centerY, int px, int py, COLORREF c)
{
    SetPixel(hdc, centerX + px, centerY + py, c);
    SetPixel(hdc, centerX - px, centerY + py, c);
    SetPixel(hdc, centerX + px, centerY - py, c);
    SetPixel(hdc, centerX - px, centerY - py, c);
}