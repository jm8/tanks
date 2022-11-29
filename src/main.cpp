#include "src/common.h"
#include "src/menu.h"
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
    while (true) {
        gameState->mouseDown = LCD.Touch(&gameState->mouseX, &gameState->mouseY);
        double newT = TimeNow();
        gameState->update(t - newT);
        gameState->draw();
        t = newT;
    }
    return 0;
}
