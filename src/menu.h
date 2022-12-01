#pragma once
#include "src/gamestate.h"
#include "src/statistics.h"
#include <string>
#include <vector>

class Menu : public GameState {
  public:
    Menu(Statistics *statistics) : statistics(statistics) {
    }

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
    Statistics *statistics;
    bool playPressed = false;

    void writeStrings(std::vector<std::string> strings);
};
