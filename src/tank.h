#pragma once
#include "common.h"
#include <FEHImages.h>
#include <iostream>
#include <utility>

using namespace std;

class Tank {
  public:
    Tank(char lor) {

        leftOrRight = lor;
        if (lor == 'l') {
            xPos = LCD_WIDTH / 4; // change to randomized value
            tankImg.Open("icons/left tank.pic");
        } else if (lor == 'r') {
            xPos = 3 * LCD_WIDTH / 4; // change to randomized value
        } else {
            cout << "Error: Tank constructor must take in l or r\n";
        }
    }

    void draw(int groundLevel) {
        yPos = groundLevel -
               TANK_DIM; // should probably be added to the constructor

        if (leftOrRight == 'l') {
            tankImg.Open("icons/left tank.pic");
        } else {
            tankImg.Open("icons/right tank.pic");
        }

        tankImg.Draw(xPos, yPos);
        // tankImg.Close();
    }

    pair<int, int> getVectorTo(int mouseX, int mouseY) {
        return pair<int, int>(mouseX - xPos, mouseY - yPos);
    }

    bool containsPoint(int x, int y) {
        return inRectangle(xPos, yPos, TANK_DIM, TANK_DIM, x, y);
    }

    int xPos, yPos;
    char leftOrRight;

  private:
    FEHImage tankImg;
};