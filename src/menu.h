#pragma once
#include "src/gamestate.h"
#include <string>
#include <vector>

class Menu : public GameState {
  public:
    bool mouseWasDown = false;
    bool mousePressed;

    enum {
        STATE_MAIN_MENU,
        STATE_STATISTICS,
        STATE_INSTRUCTIONS,
        STATE_CREDITS,
    } state = STATE_MAIN_MENU;

    void update(double dt);
    void draw();

  private:
    const char *name = "TANKS";
    const int buttonWidth = 170;
    const int buttonHeight = 32;

    void writeStrings(std::vector<std::string> strings);

    // Draw a button and returns if it's clicked
    bool button(const char *text, int x, int y, int width, int height);
};