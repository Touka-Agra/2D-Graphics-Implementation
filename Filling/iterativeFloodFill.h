#ifndef iterativeFloodFill_H
#define iterativeFloodFill_H
#include <Windows.h>
#include <stack>

using namespace std;

void iterativeFloodFill(HDC hdc, int x, int y, COLORREF fillColor, COLORREF borderColor)
{

    std::stack<std::pair<int, int>> stk;
    stk.push({x, y});

    int currentX, currentY;
    while (!stk.empty())
    {
        currentX = stk.top().first;
        currentY = stk.top().second;
        stk.pop();

        COLORREF currentColor = GetPixel(hdc, currentX, currentY);

        if (currentColor == fillColor || currentColor != borderColor)
            continue;

        SetPixel(hdc, currentX, currentY, fillColor);

        // Push neighboring pixels onto the stack
        stk.push({currentX + 1, currentY});
        stk.push({currentX - 1, currentY});
        stk.push({currentX, currentY + 1});
        stk.push({currentX, currentY - 1});
    }
}

#endif