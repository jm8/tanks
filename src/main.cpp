#include <FEHLCD.h>
#include <FEHUtility.h>
#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
using namespace std;

const vector<string> INSTRUCTIONS {
    "TANKS is a 2 player game.",
    "Goal: destroy the",
    "other tank with 3",
    "perfectly aimed shots.",
    "",
    "Aim with the mouse and",
    "click to shoot.",
    "Gravity and random wind",
    "affect the projectile.",
    
};
const vector<string> CREDITS {
    "Created by:",
    "Joshua Sims",
    "Dennis Zhitenev",
};

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
    bool mouseWasDown = false;
    bool mousePressed;

    enum {
        STATE_MAIN_MENU,
        STATE_PLAY_GAME,
        STATE_STATISTICS,
        STATE_INSTRUCTIONS,
        STATE_CREDITS,
    } state = STATE_MAIN_MENU;

    // Draws the menu (called as often as possible)
    // dt Time elapsed since last time update was called (in seconds)
    void update(double dt) {
        mousePressed = mouseDown && !mouseWasDown;
        mouseWasDown = mouseDown;
        LCD.Clear(rgb(0.9, 0.9, 0.9));
        LCD.SetFontColor(rgb(0, 0, 0));
        switch (state) {
        case STATE_MAIN_MENU: {
            LCD.WriteAt(name, center(strlen(name) * 16, LCD_WIDTH), 32);
            int topButton = 64;
            int buttonSpace = buttonHeight + 8;
            if (button("Play", center(buttonWidth, LCD_WIDTH), topButton+buttonSpace*0, buttonWidth,
                       buttonHeight)) {
                state = STATE_PLAY_GAME;
            };
            if (button("Statistics", center(buttonWidth, LCD_WIDTH),
                       topButton+buttonSpace*1, buttonWidth, buttonHeight)) {
                state = STATE_STATISTICS;
            };
            if (button("Instructions", center(buttonWidth, LCD_WIDTH),
                       topButton+buttonSpace*2, buttonWidth, buttonHeight)) {
                state = STATE_INSTRUCTIONS;
            };
            if (button("Credits", center(buttonWidth, LCD_WIDTH), topButton+buttonSpace*3,
                       buttonWidth, buttonHeight)) {
                state = STATE_CREDITS;
            };
            break;
        }
        case STATE_PLAY_GAME:
            writeStrings({"Play the game"});
            break;
        case STATE_INSTRUCTIONS:
            writeStrings(INSTRUCTIONS);
            break;
        case STATE_CREDITS:
            writeStrings(CREDITS);
            break;
        case STATE_STATISTICS:
            writeStrings({
                "Least shots:",
                "3  DAZ",
                "7  ABC",
                "12 JMS",
            });
            break;
        default:
            break;
        }

        if (state != STATE_MAIN_MENU) {
            int margin = 16;
            int backButtonWidth = 16*6;
            if (button("Back", LCD_WIDTH - backButtonWidth - margin, LCD_HEIGHT - buttonHeight - margin, backButtonWidth, buttonHeight)) {
                state = STATE_MAIN_MENU;
            }
        }
    }

  private:
    const char *name = "TANKS";
    const int buttonWidth = 170;
    const int buttonHeight = 32;

    void writeStrings(vector<string> strings) {
        for (int i = 0; i < strings.size(); i++) {
            LCD.WriteAt(strings[i].c_str(), 16, 16+18*i);
        }
    }

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
        LCD.WriteAt(text, x + 8, y + center(16, buttonHeight));
        return hover && mousePressed;
    }
};

class Tank {
  public:
    Tank(char lor) {

        leftOrRight = lor;
        if (lor == 'l') {
            xPos = LCD_WIDTH / 4; // change to randomized value
        } else if (lor == 'r') {
            xPos = 3 * LCD_WIDTH / 4; // change to randomized value
        } else {
            cout << "Error: Tank constructor must take in l or r\n";
        }
    }

    void draw(int groundLevel) {
        yPos = groundLevel; // should add height of tank
        // actually draw tank
    }

    pair<int, int> getVectorTo(int mouseX, int mouseY) {
        return pair<int, int>(mouseX-xPos, mouseY-yPos);
    }

  private:
    int xPos, yPos;
    char leftOrRight;
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
