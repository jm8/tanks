#include "common.h"
#include "game.h"
#include "menu.h"
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
    GameState *gameState;
    gameState = new Menu();

    // Initializes shouldPlay and mouseWasPressed
    bool shouldPlay = false;
    bool mouseWasPressed = false;

    // Infinite game loop
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
            gameState = new Menu();
        } else if (action == SWITCH_STATE_GOTO_WIN_LEFT) {
            int numberOfShots = dynamic_cast<Game *>(gameState)->numberOfShots;
            delete gameState;
            gameState = new WinScreen(LEFT, numberOfShots);
        } else if (action == SWITCH_STATE_GOTO_WIN_RIGHT) {
            int numberOfShots = dynamic_cast<Game *>(gameState)->numberOfShots;
            delete gameState;
            gameState = new WinScreen(RIGHT, numberOfShots);
        }
        t = newT;
    }
    return 0;
}
