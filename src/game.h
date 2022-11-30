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

    Game() {
        windStrength = randBetween(-5, 5);
    }

    SwitchStateAction update(double dt) {
        vector = currentTank->getVectorTo(mouseX, mouseY);

        if (!projectile && mouseJustPressed) {
            projectile = make_optional<Projectile>(
                vector.x, vector.y, vector.dx * SHOT_STRENGTH,
                vector.dy * SHOT_STRENGTH, windStrength);
        }

        if (projectile) {
            projectile->update(dt);
            if (projectile->shouldDelete() || castle.containsPoint(projectile->xPos, projectile->yPos)
                || inRectangle(0, leftGroundLevel, groundDipLocation, LCD_HEIGHT - leftGroundLevel,
                projectile->xPos, projectile->yPos) || inRectangle(groundDipLocation, rightGroundLevel,
                LCD_WIDTH - groundDipLocation, LCD_HEIGHT - rightGroundLevel, projectile->xPos, projectile->yPos)) {
                // swapTurn();
                projectile.reset();
            } else if (otherTank->containsPoint(projectile->xPos, projectile->yPos)) {
                otherTank->drawExplosion();
                if (!otherTank->removeLife()) {
                    if (currentTank == &leftTank) {
                        return SWITCH_STATE_GOTO_WIN_LEFT;
                    } else {
                        return SWITCH_STATE_GOTO_WIN_RIGHT;
                    }
                } else {
                    // swapTurn();
                    projectile.reset();
                }
            } else if (backButton()) {
                return SWITCH_STATE_GOTO_MENU;
            }
        }

        return SWITCH_STATE_STAY;
    }

    void draw() {
        LCD.Clear(SKY_COLOR);

        drawWindHUD();

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

    int numberOfShots = 0;

  private:
    int rightGroundLevel = LCD_HEIGHT - 16;
    int leftGroundLevel = randBetween(LCD_HEIGHT / 2, rightGroundLevel - 25);
    int windStrength;
    Tank leftTank = Tank(LEFT, leftGroundLevel);
    Tank rightTank = Tank(RIGHT, rightGroundLevel);
    Tank *currentTank = &leftTank;
    Tank *otherTank = &rightTank;
    Castle castle = Castle(leftGroundLevel);
    optional<Projectile> projectile;
    Vector vector;

    const int backButtonDim[4] = {10, LCD_HEIGHT-100, 170, 32};
    const int groundDipLocation = LCD_WIDTH / 2 + CASTLE_WIDTH / 2;

    bool backButton() {
        bool hover = inRectangle(backButtonDim[0], backButtonDim[1], backButtonDim[2], backButtonDim[3], mouseX, mouseY);
        if (hover) {
            LCD.SetFontColor(GUN_TIP_COLOR);
        } else {
            LCD.SetFontColor(GUN_BODY_COLOR);
        }
        LCD.FillRectangle(backButtonDim[0], backButtonDim[1], backButtonDim[2], backButtonDim[3]);
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("BACK", backButtonDim[0] + 8, backButtonDim[1] + center(16, 32));
        return hover && mouseJustPressed;
    }

    void swapTurn() {
        if (currentTank == &leftTank) {
            numberOfShots++;
        }
        projectile.reset();
        swap(currentTank, otherTank);
        vector = currentTank->getVectorTo(mouseX, mouseY);

        if (currentTank == &leftTank) {
            windStrength = randBetween(-5, 5);
        }
    }

    void drawWindHUD() {
        LCD.WriteAt("Wind Strength:", center(CHAR_WIDTH*14, LCD_WIDTH), 5);
        char arrow;
        if (windStrength > 0) {
            arrow = '>';
        } else {
            arrow = '<';
        }

        int length = abs(windStrength);
        LCD.WriteAt(string(length, arrow).c_str(), center(CHAR_WIDTH*length, LCD_WIDTH), 25);
    }
};
