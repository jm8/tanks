// #define CHEAT

#include "common.h"
#include "game.h"
#include "menu.h"
#include "statistics.h"
#include "winscreen.h"
#include <FEHUtility.h>
#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>

using namespace std;

int main() {
    double t = TimeNow();
    Statistics statistics;
    statistics.load();
    GameState *gameState;
    gameState = new Menu(&statistics);
    bool shouldPlay = false;
    bool mouseWasPressed = false;
    while (true) {
        gameState->mouseDown =
            LCD.Touch(&gameState->mouseX, &gameState->mouseY);
        gameState->mouseJustPressed = gameState->mouseDown && !mouseWasPressed;
        mouseWasPressed = gameState->mouseDown;
        double newT = TimeNow();
        SwitchStateAction action = gameState->update(newT - t);
        gameState->draw();
        if (action == SWITCH_STATE_GOTO_GAME) {
            delete gameState;
            gameState = new Game();
        } else if (action == SWITCH_STATE_GOTO_MENU) {
            delete gameState;
            gameState = new Menu(&statistics);
        } else if (action == SWITCH_STATE_GOTO_WIN_LEFT) {
            int numberOfShots = dynamic_cast<Game *>(gameState)->numberOfShots;
            delete gameState;
            gameState = new WinScreen(LEFT, numberOfShots, &statistics);
        } else if (action == SWITCH_STATE_GOTO_WIN_RIGHT) {
            int numberOfShots = dynamic_cast<Game *>(gameState)->numberOfShots;
            delete gameState;
            gameState = new WinScreen(RIGHT, numberOfShots, &statistics);
        }
        t = newT;
    }
    return 0;
}
