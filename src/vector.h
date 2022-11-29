#pragma once
#include <utility>
#include <iostream>
#include <FEHLCD.h>
using namespace std;
class Vector {
  public:

    Vector() {}
    
    // Creates a vector origin (x, y) that goes right by dx and up by dy
    Vector(double x, double y, double dx, double dy)
        : x(x), y(y), dx(dx), dy(dy) {
    }

    void draw() {
        LCD.SetFontColor(WHITE);
        drawLine(x, y, x+dx, y+dy);
    }

private:
    void drawLine(int x0, int y0, int x1, int y1) {
        int dx = abs(x1 - x0);
        int sx = x0 < x1 ? 1 : -1;
        int dy = -abs(y1 - y0);
        int sy = y0 < y1 ? 1 : -1;
        int error = dx + dy;
        
        // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
        while (true) {
            LCD.DrawPixel(x0, y0);
            if (x0 == x1 && y0 == y1) break;
            int e2 = 2 * error;
            if (e2 >= dy) {
                if (x0 == x1) break;
                error = error + dy;
                x0 = x0 + sx;
            }
            if (e2 <= dx) {
                if (y0 == y1) break;
                error = error + dx;
                y0 = y0 + sy;
            }
        }
    }

  public:
    double x, y;
    double dx, dy;
};