#pragma once
#include <FEHLCD.h>

using namespace std;

class Projectile {

    public:

    double xPos, yPos;

    Projectile(double x, double y, double vx, double vy, int ws) {
        xPos = x;
        yPos = y;
        xVel = x;
        yVel = y;
        windStrength = ws;
    }

    void update(double gravity, double dt) {
        xPos += xVel*dt;
        yVel += gravity*dt;
        yPos += yVel*dt;
    }

    void draw() {
        LCD.FillCircle(xPos, yPos, 2);
    }

    private:
    double xVel, yVel;
    int windStrength;
};