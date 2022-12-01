#include "common.h"
#include <FEHLCD.h>
#pragma once

enum SwitchStateAction : int {
    SWITCH_STATE_STAY,
    SWITCH_STATE_GOTO_GAME,
    SWITCH_STATE_GOTO_WIN_LEFT,
    SWITCH_STATE_GOTO_WIN_RIGHT,
    SWITCH_STATE_GOTO_MENU,
};

const int buttonHeight = 32;

class GameState {
  public:
    int mouseX, mouseY;
    bool mouseDown;
    bool mouseJustPressed;

    virtual SwitchStateAction update(double dt) = 0;
    virtual void draw() = 0;

    // Draw a button and returns if it's clicked
    bool button(const char *text, int x, int y, int width, int height) {
        bool hover = inRectangle(x, y, width, height, mouseX, mouseY);
        if (hover) {
            LCD.SetFontColor(GUN_TIP_COLOR);
        } else {
            LCD.SetFontColor(GUN_BODY_COLOR);
        }
        LCD.FillRectangle(x, y, width, height);
        LCD.SetFontColor(WHITE);
        LCD.WriteAt(text, x + 8, y + center(16, buttonHeight));
        return hover && mouseJustPressed;
    }
};
