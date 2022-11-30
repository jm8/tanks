#pragma once
#include "common.h"
#include "vector.h"
#include <FEHImages.h>
#include <cmath>
#include <iostream>
#include <utility>

using namespace std;

class Tank {
  public:
    Tank(char lor, int groundLevel) {

        health = 3;
        yPos = groundLevel - TANK_DIM;
        leftOrRight = lor;

        int eighth = LCD_WIDTH / 8;

        if (lor == 'l') {
            xPos = randBetween(eighth, 3 * eighth);
            tankImg.Open("icons/left tank.pic");
        } else if (lor == 'r') {
            xPos = randBetween(5 * eighth, 7 * eighth);
            tankImg.Open("icons/right tank.pic");
        } else {
            cout << "Error: Tank constructor must take in l or r\n";
        }

        heartImg.Open("icons/heart.pic");
    }

    void draw() {
        tankImg.Draw(xPos, yPos);

        if (leftOrRight == 'l') {
            for (int i = 0; i < health; i++) {
                heartImg.Draw(5+i*12, 5);
            }
        } else {
            for (int i = 0; i < health; i++) {
                heartImg.Draw(LCD_WIDTH-15-i*12, 5);
            }
        }
    }

    // Removes a life and returns if the tank is alive or not
    bool removeLife() {
        return --health;
    }

    Vector getVectorTo(int mouseX, int mouseY) {
        auto [x0, y0] = gunTipPosition(mouseX, mouseY);
        return Vector(x0, y0, mouseX - x0, mouseY - y0);
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
        int x1 = x0 + (leftOrRight == 'l' ? 6 : -6);
        int y1 = y0;
        drawLine(x0, y0, x1, y1);
        LCD.SetFontColor(GUN_TIP_COLOR);
        LCD.DrawPixel(x1, y1);
    }

  private:
    pair<int, int> gunBasePosition() {
        return make_pair(xPos + (leftOrRight == 'l' ? 8 : 6), yPos + 3);
    }

    pair<int, int> gunTipPosition(int mouseX, int mouseY) {
        auto [x0, y0] = gunBasePosition();
        int dx = mouseX - x0;
        int dy = mouseY - y0;
        double dist = sqrt(dx * dx + dy * dy);
        return make_pair(x0 + GUN_LENGTH * dx / dist,
                         y0 + GUN_LENGTH * dy / dist);
    }

    int xPos, yPos;
    FEHImage tankImg, heartImg;
    char leftOrRight;
    int health;
};
