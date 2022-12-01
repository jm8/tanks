#pragma once
#include <FEHLCD.h>
#include <FEHRandom.h>

const int LCD_WIDTH = 320;
const int LCD_HEIGHT = 240;
const int TANK_DIM = 14;
const int GUN_LENGTH = 6;
const int CASTLE_HEIGHT = 49;
const int CASTLE_WIDTH = 25;
const int VEL_COMP = 2;
const int GRAVITY = 125;
const double SHOT_STRENGTH = 2.5;
const double TIME_MULTIPLIER = 1.5;
const int CHAR_WIDTH = 12;
const int MAX_VECTOR_LENGTH = 100;

// colors
const unsigned int SKY_COLOR = 0x13254f;
const unsigned int GUN_BODY_COLOR = 0x817e5b;
const unsigned int GUN_TIP_COLOR = 0xbab37c;
const unsigned int GROUND_COLOR = 0x484735;

// Returns true if the point (px, py) is in the rectangle with top left (rx, ry)
// with size (rw, rh)
bool inRectangle(int rx, int ry, int rw, int rh, int px, int py) {
    return px >= rx && px <= rx + rw && py >= ry && py <= ry + rh;
}

int randBetween(int low, int high) {
    return low + Random.RandInt() % (high - low);
}

// Returns the x coordinate of the left position needed to center
// something of width size in something of width max_size. (also works with y
// coordinates)
int center(int size, int max_size) {
    return (max_size - size) / 2;
};

// Draws a line from (x1, y1) to (x2, y2)
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
