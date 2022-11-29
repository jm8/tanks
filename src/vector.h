#pragma once
#include <FEHLCD.h>
class Vector {
  public:
    // Creates a vector origin (x, y) that goes right by dx and up by dy
    Vector(double x, double y, double dx, double dy)
        : x(x), y(y), dx(dx), dy(dy) {
    }

    void draw() {
        LCD.SetFontColor(WHITE);
        // LCD.DrawLine(x, y, x+dx, y+dy);
    }

    double x, y;
    double dx, dy;
};