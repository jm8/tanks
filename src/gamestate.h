#pragma once

enum SwitchStateAction : int {
    SWITCH_STATE_STAY,
    SWITCH_STATE_GOTO_GAME,
    SWITCH_STATE_GOTO_MENU,
};

class GameState {
public:
    int mouseX, mouseY;
    bool mouseDown;

    virtual SwitchStateAction update(double dt) = 0;
    virtual void draw() = 0;
};
