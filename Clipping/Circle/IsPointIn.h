//
// Created by LENOVO on 6/5/2025.
//

#ifndef INC_2D_GRAPHICS_IMPLEMENTATION_ISPOINTIN_H
#define INC_2D_GRAPHICS_IMPLEMENTATION_ISPOINTIN_H

bool isPointInsideCircle(int x, int y, int cx, int cy, int r) {
    int dx = x - cx;
    int dy = y - cy;
    return dx * dx + dy * dy <= r * r;
}

#endif //INC_2D_GRAPHICS_IMPLEMENTATION_ISPOINTIN_H
