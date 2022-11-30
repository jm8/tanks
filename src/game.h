#pragma once
#include "LCDColors.h"
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
            if (projectile->shouldDelete() || castle.containsPoint(projectile->xPos, projectile->yPos)) {
                swapTurn();
            } else if (otherTank->containsPoint(projectile->xPos, projectile->yPos)) {
                if (!otherTank->removeLife()) {
                    return SWITCH_STATE_GOTO_MENU; // TODO: add win screen state
                } else {
                    swapTurn();
                }
            }
        }

        return SWITCH_STATE_STAY;
    }

    void draw() {
        LCD.Clear(SKY_COLOR);

        LCD.SetFontColor(GROUND_COLOR);
        LCD.FillRectangle(0, leftGroundLevel, groundDipLocation,
                          LCD_HEIGHT - leftGroundLevel);

        LCD.SetFontColor(GROUND_COLOR);
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
    Tank leftTank = Tank(LEFT, leftGroundLevel);
    Tank rightTank = Tank(RIGHT, rightGroundLevel);
    Tank *currentTank = &leftTank;
    Tank *otherTank = &rightTank;
    Castle castle = Castle(leftGroundLevel);
    optional<Projectile> projectile;
    Vector vector;

    const int groundDipLocation = LCD_WIDTH / 2 + CASTLE_WIDTH / 2;

    void swapTurn() {
        projectile.reset();
        swap(currentTank, otherTank);
        vector = currentTank->getVectorTo(mouseX, mouseY);
    }
};
