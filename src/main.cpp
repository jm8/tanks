#include "FEHLCD.h"
#include "FEHUtility.h"
#include <cmath>
#include <memory>
#include <sstream>
using namespace std;

// Turns floats r, g, b (0 to 1) into a unsigned int color for use in LCD
// eg ```rgb(1, 0.5, 0) == 0xff8000```
unsigned int rgb(float r, float g, float b) {
    return ((int)(r * 255) << 16) | ((int)(g * 255) << 8) | (int)(b * 255);
}

// Returns true if the point (px, py) is in the rectangle with top left (rx, ry)
// with size (rw, rh)
bool inRectangle(int rx, int ry, int rw, int rh, int px, int py) {
    return px >= rx && px <= rx + rw && py >= ry && py <= ry + rh;
}

const int LCD_WIDTH = 320;
const int LCD_HEIGHT = 240;

// Returns the x coordinate of the left position needed to center
// something of width size in something of width max_size. (also works with y
// coordinates)
int center(int size, int max_size) {
    return (max_size - size) / 2;
}

class Menu {
  public:
    int mouseX, mouseY;
    bool mouseDown;

    // Draws the menu (called as often as possible)
    // dt Time elapsed since last time update was called (in seconds)
    void update(double dt) {
        LCD.Clear(rgb(0.9, 0.9, 0.9));
        LCD.SetFontColor(rgb(0, 0, 0));
        LCD.WriteAt(name, center(strlen(name) * 16, LCD_WIDTH), 32);
        button("hi", center(buttonWidth, LCD_WIDTH), 64, buttonWidth,
               buttonHeight);
    }

  private:
    const char *name = "TANKS";
    const int buttonWidth = 170;
    const int buttonHeight = 32;

    // Draw a button and returns if it's clicked
    bool button(const char *text, int x, int y, int width, int height) {
        bool hover = inRectangle(x, y, width, height, mouseX, mouseY);
        if (hover) {
            LCD.SetFontColor(rgb(.4, .4, .9));
        } else {
            LCD.SetFontColor(rgb(.2, .2, .9));
        }
        LCD.FillRectangle(x, y, width, height);
        LCD.SetFontColor(rgb(1, 1, 1));
        LCD.WriteAt(text, x + 16, y + center(16, buttonHeight));
        return hover && mouseDown;
    }
};

int main() {
    Menu menu;
    double t = TimeNow();
    while (true) {
        menu.mouseDown = LCD.Touch(&menu.mouseX, &menu.mouseY);
        double newT = TimeNow();
        menu.update(t - newT);
        t = newT;
    }
    return 0;
}
