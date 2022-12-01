#pragma once
#include "common.h"
#include <FEHImages.h>

using namespace std;

// Draws a castle
// By Dennis
class Castle {
  public:
    // Load the image and calculate the position
    // By Dennis
    Castle(int groundLevel) {
        castleImg.Open("icons/castle.pic");
        xPos = (LCD_WIDTH - CASTLE_WIDTH) / 2;
        yPos = groundLevel - CASTLE_HEIGHT;
        // castleImg.Close();
    }

    // Draw castle image
    // By Dennis
    void draw() {
        castleImg.Draw(xPos, yPos);
    }

    // Check if there is a collision between the point and the castle
    // by Dennis
    bool containsPoint(int x, int y) {
        return inRectangle(xPos, yPos, CASTLE_WIDTH, CASTLE_HEIGHT, x, y);
    }

  private:
    int xPos, yPos;
    FEHImage castleImg;
};
