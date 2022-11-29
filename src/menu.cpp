#include "src/menu.h"
#include "src/common.h"
#include "game.h"
#include <FEHLCD.h>
#include <iostream>

using namespace std;

const vector<string> INSTRUCTIONS{
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
const vector<string> CREDITS{
    "Created by:",
    "Joshua Sims",
    "Dennis Zhitenev",
};

void Menu::update(double dt) {
    mousePressed = mouseDown && !mouseWasDown;
    mouseWasDown = mouseDown;
}

void Menu::draw() {
    cout << mouseX << endl;
    LCD.Clear(rgb(0.9, 0.9, 0.9));
    LCD.SetFontColor(rgb(0, 0, 0));
    switch (state) {
    case STATE_MAIN_MENU: {
        LCD.WriteAt(name, center(strlen(name) * 16, LCD_WIDTH), 32);
        int topButton = 64;
        int buttonSpace = buttonHeight + 8;
        if (button("Play", center(buttonWidth, LCD_WIDTH),
                   topButton + buttonSpace * 0, buttonWidth, buttonHeight)) {
            
        };
        if (button("Statistics", center(buttonWidth, LCD_WIDTH),
                   topButton + buttonSpace * 1, buttonWidth, buttonHeight)) {
            state = STATE_STATISTICS;
        };
        if (button("Instructions", center(buttonWidth, LCD_WIDTH),
                   topButton + buttonSpace * 2, buttonWidth, buttonHeight)) {
            state = STATE_INSTRUCTIONS;
        };
        if (button("Credits", center(buttonWidth, LCD_WIDTH),
                   topButton + buttonSpace * 3, buttonWidth, buttonHeight)) {
            state = STATE_CREDITS;
        };
        break;
    }
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
        int backButtonWidth = 16 * 6;
        if (button("Back", LCD_WIDTH - backButtonWidth - margin,
                   LCD_HEIGHT - buttonHeight - margin, backButtonWidth,
                   buttonHeight)) {
            state = STATE_MAIN_MENU;
        }
    }
}

void Menu::writeStrings(vector<string> strings) {
    for (int i = 0; i < strings.size(); i++) {
        LCD.WriteAt(strings[i].c_str(), 16, 16 + 18 * i);
    }
}

// Draw a button and returns if it's clicked
bool Menu::button(const char *text, int x, int y, int width, int height) {
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