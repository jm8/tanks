#pragma once
#include "common.h"
#include <FEHLCD.h>
#include <cmath>
#include <iostream>
#include <math.h>
#include <utility>

using namespace std;

// A Projectile object represents the projectile shot by the tanks.
// Each object keeps track of the x and y positions, x and y
// velocities, and the wind strength
// Mostly by Dennis
class Projectile {

  public:
    double xPos, yPos;

    // Initializes the position, velocity, and wind strength
    // By Dennis
    Projectile(double x, double y, double vx, double vy, int ws) {
        xPos = x;
        yPos = y;
        xVel = vx;
        yVel = vy;
        windStrength = ws;
    }

    // 
    void update(double dt) {
        dt *= TIME_MULTIPLIER;
#ifndef CHEAT
        xVel += windStrength * 5 * dt;
        yVel += GRAVITY * dt;
#endif
        xPos += xVel * dt;
        yPos += yVel * dt;
    }

    bool shouldDelete() {
        if (yPos > LCD_HEIGHT || xPos < 0 || xPos > LCD_WIDTH) {
            return true;
        } else {
            return false;
        }
    }

    void draw() {
        LCD.SetFontColor(WHITE);
        LCD.FillCircle(xPos, yPos, 2);
    }

  private:
    double xVel, yVel;
    int windStrength;
};
