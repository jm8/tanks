#pragma once
#include "src/gamestate.h"
#include "src/statistics.h"
#include <string>
#include <vector>

// The Menu
class Menu : public GameState {
  public:
    Menu(Statistics *statistics) : statistics(statistics) {
    }

    // The menu state for the different parts of the menu
    enum {
        STATE_MAIN_MENU,
        STATE_STATISTICS,
        STATE_INSTRUCTIONS,
        STATE_CREDITS,
    } state = STATE_MAIN_MENU;

    SwitchStateAction update(double dt);
    void draw();

  private:
    // constants
    const char *name = "TANKS";
    const int buttonWidth = 170;

    Statistics *statistics;
    bool playPressed = false;

    // Write a bunch of strings to the screen (for instructions and credits).
    void writeStrings(std::vector<std::string> strings);
};
