#pragma once
#include <string>
#include <vector>

class Menu {
  public:
    int mouseX, mouseY;
    bool mouseDown;
    bool mouseWasDown = false;
    bool mousePressed;

    enum {
        STATE_MAIN_MENU,
        STATE_STATISTICS,
        STATE_INSTRUCTIONS,
        STATE_CREDITS,
    } state = STATE_MAIN_MENU;

    // Draws the menu (called as often as possible)
    // dt Time elapsed since last time update was called (in seconds)
    // returns true if it should play the game
    bool update(double dt);

  private:
    const char *name = "TANKS";
    const int buttonWidth = 170;
    const int buttonHeight = 32;

    void writeStrings(std::vector<std::string> strings);

    // Draw a button and returns if it's clicked
    bool button(const char *text, int x, int y, int width, int height);
};