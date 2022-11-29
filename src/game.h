#pragma once
#include <FEHRandom.h>
#include "common.h"
#include "tank.h"
#include "castle.h"

using namespace std;

class Game : public GameState {

  public:
    Game() : leftTank('l'), rightTank('r') {
        rightGroundLevel = LCD_HEIGHT - 16;
        leftGroundLevel = randBetween(LCD_HEIGHT / 2, rightGroundLevel - 25);
    }

    void draw() {
        LCD.Clear(0x05214d);

        leftTank.draw(leftGroundLevel);

        LCD.SetFontColor(groundColor);
        LCD.FillRectangle(0, leftGroundLevel, groundDipLocation,
                          LCD_HEIGHT - leftGroundLevel);

        rightTank.draw(rightGroundLevel);

        LCD.SetFontColor(groundColor);
        LCD.FillRectangle(groundDipLocation, rightGroundLevel,
                          LCD_WIDTH - groundDipLocation,
                          LCD_HEIGHT - rightGroundLevel);

        castle.draw(leftGroundLevel);
    }

    SwitchStateAction update(double dt) {
      return SWITCH_STATE_STAY;
    }

    bool mouseDown;
    int mouseX;
    int mouseY;

  private:
    Tank leftTank;
    Tank rightTank;
    Castle castle;
    int leftGroundLevel;
    int rightGroundLevel;

    unsigned int groundColor = 0x705301;
    int groundDipLocation = LCD_WIDTH / 2 + CASTLE_WIDTH / 2;
};