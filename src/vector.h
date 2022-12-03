#pragma once
#include "common.h"
#include <FEHLCD.h>
#include <cmath>
#include <iostream>
#include <utility>
using namespace std;

// A Vector object represents the line used to aim the tank
// Mostly by Josh
class Vector {
  public:
    // Empty constructor to appease the C++ compiler
    Vector() {
    }

    // Creates a vector origin (x, y) that goes right by dx and down by dy
    // By Josh
    Vector(double x, double y, double dx, double dy)
        : x(x), y(y), dx(dx), dy(dy) {
    }

    // Returns the length of the vector
    // By Josh
    double length() {
        return sqrt(dx * dx + dy * dy);
    }

    // Draws the vector (a line from (x, y) that goes right
    // by dx and down by dy)
    // By Josh
    void draw() {
        LCD.SetFontColor(WHITE);
        // skip a few pixels when drawing
        int skipLength = 4;
        double l = length();

        // Prevents dividing by zero
        if (l < 1) {
            return;
        }
        double xn = dx / l;
        double yn = dy / l;
        int x0 = x + xn * skipLength;
        int y0 = y + yn * skipLength;
        int x1 = x + dx;
        int y1 = y + dy;

        drawLine(x0, y0, x1, y1);
    }

  public:
    double x, y;
    double dx, dy;
};
