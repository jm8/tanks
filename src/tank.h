#pragma once
#include "FEHUtility.h"
#include "common.h"
#include "vector.h"
#include <FEHImages.h>
#include <FEHUtility.h>
#include <cmath>
#include <iostream>
#include <utility>

using namespace std;

enum { RIGHT, LEFT };

class Tank {
  public:
    Tank(int lor, int groundLevel) {

        health = 3;
        yPos = groundLevel - TANK_DIM;
        leftOrRight = lor;

        int eighth = LCD_WIDTH / 8;

        if (lor == RIGHT) {
            xPos = randBetween(5 * eighth, 7 * eighth);
            tankImg.Open("icons/right tank.pic");
        } else if (lor == LEFT) {
            xPos = randBetween(eighth, 3 * eighth);
            tankImg.Open("icons/left tank.pic");
        } else {
            cout << "Error: Tank constructor must take in LEFT or RIGHT\n";
        }

        heartImg.Open("icons/heart.pic");
    }

    void draw() {
        tankImg.Draw(xPos, yPos);

        if (leftOrRight) {
            for (int i = 0; i < health; i++) {
                heartImg.Draw(5 + i * 12, 5);
            }
        } else {
            for (int i = 0; i < health; i++) {
                heartImg.Draw(LCD_WIDTH - 15 - i * 12, 5);
            }
        }
    }

    // Removes a life and returns if the tank is alive or not
    bool removeLife() {
        return --health;
    }

    Vector getVectorTo(int mouseX, int mouseY) {
        auto [mx, my] = limitMousePosition(mouseX, mouseY);
        auto [x0, y0] = gunTipPosition(mx, my);

        Vector result(x0, y0, mx - x0, my - y0);

        if (result.length() > MAX_VECTOR_LENGTH) {
            result = Vector(x0, y0,
                            (result.dx) / result.length() * MAX_VECTOR_LENGTH,
                            (result.dy) / result.length() * MAX_VECTOR_LENGTH);
        }

        return result;
    }

    bool containsPoint(int x, int y) {
        return inRectangle(xPos, yPos, TANK_DIM, TANK_DIM, x, y);
    }

    void drawGunPointing(int mouseX, int mouseY) {
        LCD.SetFontColor(GUN_BODY_COLOR);
        auto [x0, y0] = gunBasePosition();
        auto [x1, y1] = gunTipPosition(mouseX, mouseY);
        drawLine(x0, y0, x1, y1);
        LCD.SetFontColor(GUN_TIP_COLOR);
        LCD.DrawPixel(x1, y1);
    }

    void drawGunStraight() {
        LCD.SetFontColor(GUN_BODY_COLOR);
        auto [x0, y0] = gunBasePosition();
        int x1 = x0 + (leftOrRight == LEFT ? 6 : -6);
        int y1 = y0;
        drawLine(x0, y0, x1, y1);
        LCD.SetFontColor(GUN_TIP_COLOR);
        LCD.DrawPixel(x1, y1);
    }

    void drawExplosion() {
        FEHImage explosionImg;
        explosionImg.Open("icons/explosion.pic");
        explosionImg.Draw(xPos - 5, yPos - 5);
        Sleep(500);
    }

  private:
    pair<int, int> limitMousePosition(int mouseX, int mouseY) {
#ifdef CHEAT
        return make_pair(mouseX, mouseY);
#else
        auto [x0, y0] = gunBasePosition();

        if (leftOrRight == LEFT) {
            return make_pair(max(mouseX, x0), min(mouseY, y0));
        } else {
            return make_pair(min(mouseX, x0), min(mouseY, y0));
        }
#endif
    }

    pair<int, int> gunBasePosition() {
        // return make_pair(xPos + (leftOrRight == LEFT ? 8 : 6), yPos + 3);
        return make_pair(xPos + 6 + leftOrRight * 2, yPos + 3);
    }

    pair<int, int> tipPosition;
    pair<int, int> gunTipPosition(int mouseX, int mouseY) {
        auto [x0, y0] = gunBasePosition();
        auto [mx, my] = limitMousePosition(mouseX, mouseY);
        int dx = mx - x0;
        int dy = my - y0;
        double dist = sqrt(dx * dx + dy * dy);
        if (dist > 1) {
            tipPosition = make_pair(x0 + GUN_LENGTH * dx / dist,
                                    y0 + GUN_LENGTH * dy / dist);
        }
        return tipPosition;
    }

    int xPos, yPos;
    FEHImage tankImg, heartImg;
    int health, leftOrRight;
};
