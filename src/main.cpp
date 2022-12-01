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

    // Sets t to the to time of the program starting
    double t = TimeNow();

    // Sets gameState to the menu
    Statistics statistics;
    statistics.load();

    // Initially menu
    GameState *gameState;
    gameState = new Menu(&statistics);

    // Initializes shouldPlay and mouseWasPressed
    bool shouldPlay = false;
    bool mouseWasPressed = false;

    // Infinite game loop
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
