#include "common.h"
#include <FEHLCD.h>
#pragma once

// The return value of GameState::update(), which tells what
// GameState to switch to
enum SwitchStateAction : int {
    SWITCH_STATE_STAY,
    SWITCH_STATE_GOTO_GAME,
    SWITCH_STATE_GOTO_WIN_LEFT,
    SWITCH_STATE_GOTO_WIN_RIGHT,
    SWITCH_STATE_GOTO_MENU,
};

const int buttonHeight = 32;

// Abstract GameState class
// by Josh
class GameState {
  public:
    // Mouse position and status. Updated by main.
    int mouseX, mouseY;
    bool mouseDown;
    bool mouseJustPressed;

    // Update function, called once per frame. dt is time elapsed in seconds.
    // Returns a SwitchStateAction to possibly change do a different GameState.
    virtual SwitchStateAction update(double dt) = 0;

    // Function called once per frame after update to draw
    virtual void draw() = 0;

    // Draw a button and returns true if it's clicked
    // by Josh
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
