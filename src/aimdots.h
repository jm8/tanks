#pragma once
#include <FEHImages.h>
#include <FEHLCD.h>
#include <vector>

using namespace std;

// Draws crosshair image where players have clicked
// by Dennis
class AimDots {

  public:
    // Loads crosshair image
    // By Dennis
    AimDots() {
        crossImg.Open("icons/crosshair.pic");
    }

    // Move one player's crosshair to a specified point
    // By Dennis
    void addPoint(int leftOrRight, int x, int y) {
        if (leftOrRight) {
            coordinates.first = pair<int, int>(x, y);
        } else {
            coordinates.second = pair<int, int>(x, y);
        }
    }

    // Draw crosshair for both players
    // By Dennis
    void draw() {
        auto [x, y] = coordinates.first;
        crossImg.Draw(x - 2, y - 2);
        auto [x2, y2] = coordinates.second;
        crossImg.Draw(x2 - 2, y2 - 2);
    }

  private:
    pair<pair<int, int>, pair<int, int>> coordinates = {{-10, -10},
                                                        {
                                                            -10,
                                                            -10,
                                                        }};
    FEHImage crossImg;
};
