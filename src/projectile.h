#pragma once
#include "common.h"
#include <FEHLCD.h>
#include <cmath>
#include <iostream>
#include <math.h>
#include <utility>

using namespace std;

class Projectile {

  public:
    double xPos, yPos;

    Projectile(double x, double y, double vx, double vy, int ws) {
        xPos = x;
        yPos = y;
        xVel = vx;
        yVel = vy;
        windStrength = ws;
        cout << "speed: " << xVel << ", " << yVel << endl;
    }

    void update(double dt) { // make gravity a constant
        dt *= TIME_MULTIPLIER;
        xPos += xVel * dt;
        yVel += GRAVITY * dt;
        yPos += yVel * dt;
    }

    bool shouldDelete() {
        if (yPos > LCD_HEIGHT) {
            return true;
        }
        return false;
    }

    void draw() {
        LCD.SetFontColor(WHITE);
        LCD.FillCircle(xPos, yPos, 2);
    }

  private:
    double xVel, yVel;
    int windStrength;
};