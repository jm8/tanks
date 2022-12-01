#include "src/common.h"

bool inRectangle(int rx, int ry, int rw, int rh, int px, int py) {
    return px >= rx && px <= rx + rw && py >= ry && py <= ry + rh;
}

int randBetween(int low, int high) {
    return low + Random.RandInt() % (high - low);
}

int center(int size, int max_size) {
    return (max_size - size) / 2;
}

unsigned int rgb(float r, float g, float b) {
    return ((int)(r * 255) << 16) | ((int)(g * 255) << 8) | (int)(b * 255);
}

void drawLine(int x1, int y1, int x2, int y2) {
    // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int error = dx + dy;

    for (int i = 0; i < 1000000; i++) {
        LCD.DrawPixel(x1, y1);
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = 2 * error;
        if (e2 >= dy) {
            if (x1 == x2)
                break;
            error = error + dy;
            x1 = x1 + sx;
        }
        if (e2 <= dx) {
            if (y1 == y2)
                break;
            error = error + dx;
            y1 = y1 + sy;
        }
    }
}
