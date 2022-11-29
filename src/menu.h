#pragma once
#include "src/gamestate.h"
#include <string>
#include <vector>

class Menu : public GameState {
  public:
    enum {
        STATE_MAIN_MENU,
        STATE_STATISTICS,
        STATE_INSTRUCTIONS,
        STATE_CREDITS,
    } state = STATE_MAIN_MENU;

    SwitchStateAction update(double dt);
    void draw();

  private:
    const char *name = "TANKS";
    const int buttonWidth = 170;
    const int buttonHeight = 32;
    bool playPressed = false;

    void writeStrings(std::vector<std::string> strings);

    // Draw a button and returns if it's clicked
    bool button(const char *text, int x, int y, int width, int height);
};