#pragma once
#include "LCDColors.h"
#include "aimdots.h"
#include "castle.h"
#include "common.h"
#include "gamestate.h"
#include "projectile.h"
#include "tank.h"
#include "vector.h"
#include <FEHRandom.h>
#include <optional>

using namespace std;

// The main Game
class Game : public GameState {

  public:
    // Chooses an initial random wind strength.
    // Also creates tanks and chooses random ground level.
    // By Dennis
    Game() {
        windStrength = randBetween(-5, 5);
    }

    // Updates vector, spawns projectile if mouse is clicked,
    // deletes projectile if it touches ground, hurts tank if it touches
    // projectile, and goes to win screen if tank is at 0 health.
    // By both people
    SwitchStateAction update(double dt) {
        vector = currentTank->getVectorTo(mouseX, mouseY);

        if (!projectile && mouseJustPressed) {
            if (currentTank == &leftTank) {
                numberOfShots++;
            }
            projectile = make_optional<Projectile>(
                vector.x, vector.y, vector.dx * SHOT_STRENGTH,
                vector.dy * SHOT_STRENGTH, windStrength);
            dots.addPoint(currentTank == &leftTank, vector.x + vector.dx,
                          vector.y + vector.dy);
        }

        if (projectile) {
            projectile->update(dt);
            if (projectile->shouldDelete()
#ifndef CHEAT
                || castle.containsPoint(projectile->xPos, projectile->yPos) ||
                inRectangle(0, leftGroundLevel, groundDipLocation,
                            LCD_HEIGHT - leftGroundLevel, projectile->xPos,
                            projectile->yPos) ||
                inRectangle(groundDipLocation, rightGroundLevel,
                            LCD_WIDTH - groundDipLocation,
                            LCD_HEIGHT - rightGroundLevel, projectile->xPos,
                            projectile->yPos)
#endif
            ) {
                swapTurn();
            } else if (otherTank->containsPoint(projectile->xPos,
                                                projectile->yPos)) {
                otherTank->drawExplosion();
                if (!otherTank->removeLife()) {
                    if (currentTank == &leftTank) {
                        return SWITCH_STATE_GOTO_WIN_LEFT;
                    } else {
                        return SWITCH_STATE_GOTO_WIN_RIGHT;
                    }
                } else {
                    swapTurn();
                }
            }
        }

        if (shouldGoBack) {
            return SWITCH_STATE_GOTO_MENU;
        }

        return SWITCH_STATE_STAY;
    }

    // Draws the background, the HUD, and all objects in the game.
    // By both people
    void draw() {
        LCD.Clear(SKY_COLOR);

        drawWindHUD();
        dots.draw();

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

        if (projectile) {
            projectile->draw();
        } else {
            vector.draw();
        }

        drawBackButton();

        drawNumberOfShots();
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
    bool shouldGoBack;
    AimDots dots;

    const int backButtonDim[4] = {10, LCD_HEIGHT - 40, 80, 32};
    const int groundDipLocation = LCD_WIDTH / 2 + CASTLE_WIDTH / 2;

    // Draw back button and respond to clicks
    // By Dennis
    void drawBackButton() {
        bool hover =
            inRectangle(backButtonDim[0], backButtonDim[1], backButtonDim[2],
                        backButtonDim[3], mouseX, mouseY);
        if (hover) {
            LCD.SetFontColor(GUN_TIP_COLOR);
        } else {
            LCD.SetFontColor(GUN_BODY_COLOR);
        }
        LCD.FillRectangle(backButtonDim[0], backButtonDim[1], backButtonDim[2],
                          backButtonDim[3]);
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("Back", backButtonDim[0] + 8,
                    backButtonDim[1] + center(16, backButtonDim[3]));
        shouldGoBack = hover && mouseJustPressed;
    }

    // Swaps currentTank and otherTank
    // Chooses random wind strength every other turn
    // by both people
    void swapTurn() {
        projectile.reset();
        swap(currentTank, otherTank);
        vector = currentTank->getVectorTo(mouseX, mouseY);

        if (currentTank == &leftTank) {
            windStrength = randBetween(-5, 5);
        }
    }

    // Draw the current wind strength
    // by Dennis
    void drawWindHUD() {
        LCD.WriteAt("Wind Strength:", center(CHAR_WIDTH * 14, LCD_WIDTH), 5);

        if (windStrength == 0) {
            LCD.WriteAt("0",
                        center(CHAR_WIDTH, LCD_WIDTH), 25);
        } else {
            char arrow;
            if (windStrength > 0) {
                arrow = '>';
            } else {
                arrow = '<';
            }

            int length = abs(windStrength);
            LCD.WriteAt(string(length, arrow).c_str(),
                        center(CHAR_WIDTH * length, LCD_WIDTH), 25);
        }
        
    }

    // Draw the current number of shots
    // By Josh
    void drawNumberOfShots() {
        LCD.SetFontColor(WHITE);
        LCD.WriteAt(numberOfShots, LCD_WIDTH - 16 - CHAR_WIDTH,
                    LCD_HEIGHT - 16 - CHAR_WIDTH);
    }
};
