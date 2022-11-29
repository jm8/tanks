#pragma once
#include "castle.h"
#include "common.h"
#include "gamestate.h"
#include "projectile.h"
#include "tank.h"
#include "vector.h"
#include <FEHRandom.h>
#include <optional>

using namespace std;

const double shot_strength = 2.5;

class Game : public GameState {

  public:
    SwitchStateAction update(double dt) {
        vector = currentTank->getVectorTo(mouseX, mouseY);

        if (mouseJustPressed) {
            projectile = make_optional<Projectile>(
                vector.x, vector.y, vector.dx * shot_strength,
                vector.dy * shot_strength, 0);
        }

        if (projectile) {
            projectile->update(dt);
        }

        return SWITCH_STATE_STAY;
    }

    void draw() {
        LCD.Clear(0x05214d);

        leftTank.draw();

        LCD.SetFontColor(groundColor);
        LCD.FillRectangle(0, leftGroundLevel, groundDipLocation,
                          LCD_HEIGHT - leftGroundLevel);

        rightTank.draw();

        LCD.SetFontColor(groundColor);
        LCD.FillRectangle(groundDipLocation, rightGroundLevel,
                          LCD_WIDTH - groundDipLocation,
                          LCD_HEIGHT - rightGroundLevel);

        castle.draw();

        vector.draw();

        if (projectile) {
            projectile->draw();
        }
    }

  private:
    int rightGroundLevel = LCD_HEIGHT - 16;
    int leftGroundLevel = randBetween(LCD_HEIGHT / 2, rightGroundLevel - 25);
    Tank leftTank = Tank('l', leftGroundLevel);
    Tank rightTank = Tank('r', rightGroundLevel);
    Tank *currentTank = &leftTank;
    Castle castle = Castle(leftGroundLevel);
    optional<Projectile> projectile;
    Vector vector;

    const unsigned int groundColor = 0x705301;
    const int groundDipLocation = LCD_WIDTH / 2 + CASTLE_WIDTH / 2;
};