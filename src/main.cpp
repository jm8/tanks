#include "common.h"
#include "menu.h"
#include "game.h"
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
        gameState->mouseDown = LCD.Touch(&gameState->mouseX, &gameState->mouseY);
        gameState->mouseJustPressed = gameState->mouseDown && !mouseWasPressed;
        mouseWasPressed = gameState->mouseDown;
        double newT = TimeNow();
        SwitchStateAction action = gameState->update(t - newT);
        gameState->draw();
        if (action == SWITCH_STATE_GOTO_GAME) {
            delete gameState;
            gameState = new Game();
        }
        t = newT;
    }
    return 0;
}
