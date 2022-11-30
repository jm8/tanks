#include "common.h"
#include "game.h"
#include "menu.h"
#include <FEHUtility.h>
#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>

using namespace std;

int main() {
    double t = TimeNow();
    GameState *gameState;
    gameState = new Menu();
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
            gameState = new Menu();
        }
        t = newT;
    }
    return 0;
}
