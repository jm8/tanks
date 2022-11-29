#pragma once
#include "common.h"
#include <FEHLCD.h>
#include <iostream>

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
        xPos += xVel * dt;
        yVel += GRAVITY * dt;
        yPos += yVel * dt;
    }

    void draw() {
        LCD.FillCircle(xPos, yPos, 2);
    }

  private:
    double xVel, yVel;
    int windStrength;
};