#pragma once
#include "common.h"
#include <FEHImages.h>

using namespace std;

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