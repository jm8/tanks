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
    LCD.DrawLine(x1, y1, x2, y2);
}
