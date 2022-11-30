#pragma once
#include "common.h"
#include <FEHLCD.h>
#include <cmath>
#include <iostream>
#include <utility>
using namespace std;

class Vector {
  public:
    Vector() {
    }

    // Creates a vector origin (x, y) that goes right by dx and up by dy
    Vector(double x, double y, double dx, double dy)
        : x(x), y(y), dx(dx), dy(dy) {
    }

    double length() {
        return sqrt(dx * dx + dy * dy);
    }

    double angle() {
        return atan2(dy, dx);
    }

    void draw() {
        LCD.SetFontColor(WHITE);
        // skip a few pixels when drawing
        int skipLength = 4;
        double l = length();
        double xn = dx / l;
        double yn = dy / l;
        int x0 = x + xn * skipLength;
        int y0 = y + yn * skipLength;
        int x1 = x + dx;
        int y1 = y + dy;
        drawLine(x0, y0, x1, y1);
    }

  private:
  public:
    double x, y;
    double dx, dy;
};
