
#ifndef recursiveFloodFill_H
#define recursiveFloodFill_H

#include <Windows.h>
#include <stack>

void recursiveFloodFill(HDC hdc, int x, int y, COLORREF fillCollor, COLORREF boarderCollor)
{
    COLORREF c = GetPixel(hdc, x, y);
    if (c == fillCollor || c == boarderCollor)
        return;
    SetPixel(hdc, x, y, fillCollor);
    recursiveFloodFill(hdc, x + 1, y, fillCollor, boarderCollor);
    recursiveFloodFill(hdc, x - 1, y, fillCollor, boarderCollor);
    recursiveFloodFill(hdc, x, y + 1, fillCollor, boarderCollor);
    recursiveFloodFill(hdc, x, y - 1, fillCollor, boarderCollor);
    return;
}

#endif