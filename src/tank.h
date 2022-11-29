#pragma once
#include "common.h"
#include "vector.h"
#include <FEHImages.h>
#include <iostream>
#include <utility>

using namespace std;

class Tank {
  public:
    Tank(char lor, int groundLevel) {

        yPos = groundLevel- TANK_DIM;
        leftOrRight = lor;
        if (lor == 'l') {
            xPos = LCD_WIDTH / 4; // change to randomized value
            tankImg.Open("icons/left tank.pic");
        } else if (lor == 'r') {
            xPos = 3 * LCD_WIDTH / 4; // change to randomized value
            tankImg.Open("icons/right tank.pic");
        } else {
            cout << "Error: Tank constructor must take in l or r\n";
        }
    }

    void draw() {

        tankImg.Draw(xPos, yPos);
        // tankImg.Close();
    }

    Vector getVectorTo(int mouseX, int mouseY) {
        return Vector(xPos, yPos, mouseX-xPos, mouseY-yPos);
    }

    bool containsPoint(int x, int y) {
        return inRectangle(xPos, yPos, TANK_DIM, TANK_DIM, x, y);
    }
  
  private:
    int xPos, yPos;
    FEHImage tankImg;
    char leftOrRight;
};