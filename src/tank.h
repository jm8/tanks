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

// A Tank object represents one of the tanks in the game, including its position and health
// Mostly by Dennis
class Tank {
  public:
    // Initializes the instance variables
    // By Dennis
    Tank(int lor, int groundLevel) {

        // Sets health to three and calculates the
        // y position that puts the tank on the ground
        health = 3;
        yPos = groundLevel - TANK_DIM;
        // Sets the side of the tank based on the enum (LEFT or RIGHT)
        leftOrRight = lor;

        int eighth = LCD_WIDTH / 8;

        // Places the tank at a random spot on the correct side of the screen
        // and opens the image that faces it the correct way
        if (lor == RIGHT) {
            xPos = randBetween(5 * eighth, 7 * eighth);
            tankImg.Open("icons/right tank.pic");
        } else if (lor == LEFT) {
            xPos = randBetween(eighth, 3 * eighth);
            tankImg.Open("icons/left tank.pic");
        } else {
            cout << "Error: Tank constructor must take in LEFT or RIGHT\n";
        }

        // Opens other images used in the class
        heartImg.Open("icons/heart.pic");
        explosionImg.Open("icons/explosion.pic");
    }

    // Draws the tank and its health
    // By Dennis
    void draw() {
        // Draws the tank image at the coordinates
        tankImg.Draw(xPos, yPos);

        // Draws the heart image in the correct corner of
        // the screen depending on leftOrRight
        // and the value in health
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
    // By Dennis
    bool removeLife() {
        return --health;
    }

    // Return the Vector object from the tank to the mouse
    // By Josh
    Vector getVectorTo(int mouseX, int mouseY) {
        // Prevents the user from aiming behind or below the tank
        auto [mx, my] = limitMousePosition(mouseX, mouseY);
        // Stores the position of the gun top in x0 and y0
        // so the vector can start from there
        auto [x0, y0] = gunTipPosition(mx, my);

        // Creates the vector
        Vector result(x0, y0, mx - x0, my - y0);

        // Limits the length of the vector to MAX_VECTOR_LENGTH
        if (result.length() > MAX_VECTOR_LENGTH) {
            result = Vector(x0, y0,
                            (result.dx) / result.length() * MAX_VECTOR_LENGTH,
                            (result.dy) / result.length() * MAX_VECTOR_LENGTH);
        }

        return result;
    }

    // Returns whether x and y are points in the tank
    // By Dennis
    bool containsPoint(int x, int y) {
        return inRectangle(xPos, yPos, TANK_DIM, TANK_DIM, x, y);
    }

    // Draws the gun of the tank pointing towards the mouse
    // By Josh
    void drawGunPointing(int mouseX, int mouseY) {
        LCD.SetFontColor(GUN_BODY_COLOR);
        auto [x0, y0] = gunBasePosition();
        auto [x1, y1] = gunTipPosition(mouseX, mouseY);
        drawLine(x0, y0, x1, y1);
        LCD.SetFontColor(GUN_TIP_COLOR);
        LCD.DrawPixel(x1, y1);
    }

    // Draws the gun of the tank pointing horizontal
    // By Josh
    void drawGunStraight() {
        LCD.SetFontColor(GUN_BODY_COLOR);
        auto [x0, y0] = gunBasePosition();
        int x1 = x0 + (leftOrRight == LEFT ? 6 : -6);
        int y1 = y0;
        drawLine(x0, y0, x1, y1);
        LCD.SetFontColor(GUN_TIP_COLOR);
        LCD.DrawPixel(x1, y1);
    }

    // Draws the explosion image generally over the tank and waits half a second
    // By Dennis
    void drawExplosion() {
        explosionImg.Draw(xPos-5, yPos-5);
        Sleep(500);
    }

  private:
    // Returns the coordinates of the mouse unless the mouse is behind or below the tank.
    // In that case, the coordinate out of bounds is set to the corresponding
    // coordinate of the gun base
    // By Josh
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
    FEHImage tankImg, heartImg, explosionImg;
    int health, leftOrRight;
};
