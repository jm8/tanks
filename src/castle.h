#pragma once
#include "common.h"
#include <FEHImages.h>

using namespace std;

class Castle {
  public:
    Castle(int groundLevel) {
        castleImg.Open("icons/castle.pic");
        xPos = (LCD_WIDTH - CASTLE_WIDTH) / 2;
        yPos = groundLevel - CASTLE_HEIGHT;
        // castleImg.Close();
    }

    void draw() {
        castleImg.Draw(xPos, yPos);
    }

    bool containsPoint(int x, int y) {
        return inRectangle(xPos, yPos, CASTLE_WIDTH, CASTLE_HEIGHT, x, y);
    }

  private:
	int xPos, yPos;
	FEHImage castleImg;
};
