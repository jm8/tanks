// https://cdn2.vectorstock.com/i/1000x1000/91/36/castle-tower-pixel-vector-41309136.jpg

#include "src/common.h"
#include "src/menu.h"
#include <FEHImages.h>
#include <FEHLCD.h>
#include <FEHRandom.h>
#include <FEHUtility.h>
#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

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
        yPos = groundLevel - TANK_DIM;

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

  private:
    int xPos, yPos;
    char leftOrRight;
    FEHImage tankImg;
};

class Castle {
  public:
    Castle() {
        castleImg.Open("icons/castle.pic");
        // castleImg.Close();
    }

    void draw(int groundLevel) {
        castleImg.Draw((LCD_WIDTH - CASTLE_WIDTH) / 2,
                       groundLevel - CASTLE_HEIGHT);
    }

  private:
    FEHImage castleImg;
};

class Game {

  public:
    Game() : leftTank('l'), rightTank('r') {
        rightGroundLevel = LCD_HEIGHT - 16;
        leftGroundLevel = randBetween(LCD_HEIGHT / 2, rightGroundLevel - 25);
    }

    void draw() {
        LCD.Clear(0x05214d);

        leftTank.draw(leftGroundLevel);

        LCD.SetFontColor(groundColor);
        LCD.FillRectangle(0, leftGroundLevel, groundDipLocation,
                          LCD_HEIGHT - leftGroundLevel);

        rightTank.draw(rightGroundLevel);

        LCD.SetFontColor(groundColor);
        LCD.FillRectangle(groundDipLocation, rightGroundLevel,
                          LCD_WIDTH - groundDipLocation,
                          LCD_HEIGHT - rightGroundLevel);

        castle.draw(leftGroundLevel);
    }

    bool mouseDown;
    int mouseX;
    int mouseY;

  private:
    Tank leftTank;
    Tank rightTank;
    Castle castle;
    int leftGroundLevel;
    int rightGroundLevel;

    unsigned int groundColor = 0x705301;
    int groundDipLocation = LCD_WIDTH / 2 + CASTLE_WIDTH / 2;
};

int main() {
    double t = TimeNow();
    Menu menu;
    bool shouldPlay = false;
    while (true) {
        menu.mouseDown = LCD.Touch(&menu.mouseX, &menu.mouseY);
        double newT = TimeNow();
        shouldPlay = menu.update(t - newT);
        // game.draw();
        t = newT;
    }
    return 0;
}
