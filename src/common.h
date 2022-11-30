#pragma once
#include <FEHLCD.h>
#include <FEHRandom.h>
// Turns floats r, g, b (0 to 1) into a unsigned int color for use in LCD
// eg ```rgb(1, 0.5, 0) == 0xff8000```
unsigned int rgb(float r, float g, float b);

// Returns true if the point (px, py) is in the rectangle with top left (rx, ry)
// with size (rw, rh)
bool inRectangle(int rx, int ry, int rw, int rh, int px, int py);

int randBetween(int low, int high);

// Returns the x coordinate of the left position needed to center
// something of width size in something of width max_size. (also works with y
// coordinates)
int center(int size, int max_size);

void drawLine(int x0, int y0, int x1, int y1);

const int LCD_WIDTH = 320;
const int LCD_HEIGHT = 240;
const int TANK_DIM = 14;
const int CASTLE_HEIGHT = 49;
const int CASTLE_WIDTH = 25;
const int VEL_COMP = 2;
const int GRAVITY = 125;
const double SHOT_STRENGTH = 2.5;
const double TIME_MULTIPLIER = 1.5;
const unsigned int GROUND_COLOR = 0x705301;
const unsigned int SKY_COLOR = 0x05214d;