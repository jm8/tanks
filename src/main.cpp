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
    // Load statistics
    Statistics statistics;
    statistics.load();

    // Initially menu
    GameState *gameState;
    gameState = new Menu(&statistics);

    // if the mouse was pressed last frame
    bool mouseWasPressed = false;

    // Current time
    double t = TimeNow();
    while (true) {
        // Update mouse information
        gameState->mouseDown =
            LCD.Touch(&gameState->mouseX, &gameState->mouseY);
        gameState->mouseJustPressed = gameState->mouseDown && !mouseWasPressed;
        mouseWasPressed = gameState->mouseDown;

        // Call update and draw on current gameState.
        double newT = TimeNow();
        SwitchStateAction action = gameState->update(newT - t);
        gameState->draw();
        t = newT;

        // Switch state if necessary.
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
    }
    return 0;
}
