#pragma once
#include <vector>
#include <FEHLCD.h>
#include <FEHImages.h>

using namespace std;

class AimDots {

    public:

    AimDots() {
        crossImg.Open("icons/crosshair.pic");
    }

    void addPoint(int leftOrRight, int x, int y) {
        if (leftOrRight) {
            coordinates.first = pair<int, int>(x, y);
        } else {
            coordinates.second = pair<int, int>(x, y);
        }
    }

    void draw() {
        auto [x, y] = coordinates.first;
        crossImg.Draw(x-2, y-2);
        auto [x2, y2] = coordinates.second;
        crossImg.Draw(x2-2, y2-2);
    }

    private:
    pair<pair<int, int>, pair<int, int>> coordinates = {{-10, -10}, {-10, -10,}};
    FEHImage crossImg;
};
