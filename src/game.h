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

class Game : public GameState {

  public:
    SwitchStateAction update(double dt) {
        vector = currentTank->getVectorTo(mouseX, mouseY);

        if (!projectile && mouseJustPressed) {
            projectile = make_optional<Projectile>(
                vector.x, vector.y, vector.dx * SHOT_STRENGTH,
                vector.dy * SHOT_STRENGTH, 0);
        }

        if (projectile) {
            projectile->update(dt);
            if (projectile->shouldDelete()) {
                projectile.reset();
                swap(currentTank, otherTank);
                vector = currentTank->getVectorTo(mouseX, mouseY);
            }
        }

        return SWITCH_STATE_STAY;
    }

    void draw() {
        LCD.Clear(0x05214d);

        LCD.SetFontColor(groundColor);
        LCD.FillRectangle(0, leftGroundLevel, groundDipLocation,
                          LCD_HEIGHT - leftGroundLevel);

        LCD.SetFontColor(groundColor);
        LCD.FillRectangle(groundDipLocation, rightGroundLevel,
                          LCD_WIDTH - groundDipLocation,
                          LCD_HEIGHT - rightGroundLevel);

        currentTank->draw();
        currentTank->drawGunPointing(mouseX, mouseY);

        otherTank->draw();
        otherTank->drawGunStraight();

        castle.draw();

        if (!projectile)
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
    Tank *otherTank = &rightTank;
    Castle castle = Castle(leftGroundLevel);
    optional<Projectile> projectile;
    Vector vector;

    const unsigned int groundColor = 0x705301;
    const int groundDipLocation = LCD_WIDTH / 2 + CASTLE_WIDTH / 2;
};