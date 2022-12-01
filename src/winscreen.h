#include "common.h"
#include "gamestate.h"
#include "src/statistics.h"
#include "tank.h"
#include <FEHLCD.h>
#include <array>
#include <sstream>

class WinScreen : public GameState {

  public:
    WinScreen(int player, int numberOfShots, Statistics *statistics)
        : player(player), numberOfShots(numberOfShots), statistics(statistics) {
    }

    SwitchStateAction update(double dt) {
        if (shouldSubmit) {
            statistics->push({numberOfShots, initials});
            statistics->save();
            return SWITCH_STATE_GOTO_MENU;
        }
        return SWITCH_STATE_STAY;
    }

    void draw() {
        LCD.Clear(SKY_COLOR);

        const char *congrats =
            player == LEFT ? "LEFT PLAYER WINS!" : "RIGHT PLAYER WINS!";
        LCD.SetFontColor(WHITE);
        LCD.WriteAt(congrats, center(strlen(congrats) * CHAR_WIDTH, LCD_WIDTH),
                    32);

        LCD.SetFontColor(WHITE);
        string s = "It took " + to_string(numberOfShots) + " shots.";
        LCD.WriteAt(s.c_str(), center(s.size() * CHAR_WIDTH, LCD_WIDTH),
                    32 + 18);

        const char *enterYourInitials = "Enter your initials:";
        LCD.WriteAt(enterYourInitials,
                    center(strlen(enterYourInitials) * CHAR_WIDTH, LCD_WIDTH),
                    32 + 3 * 18);

        int centerInitialX = center(initialsWidth, LCD_WIDTH);
        int initialsY = 32 + 5 * 18;
        getInitials(&initials[0], centerInitialX - initialsSpacing, initialsY);
        getInitials(&initials[1], centerInitialX, initialsY);
        getInitials(&initials[2], centerInitialX + initialsSpacing, initialsY);

        int submitWidth = (strlen("Submit") - 1) * CHAR_WIDTH + 2 * 16;

        if (button("Submit", center(submitWidth, LCD_WIDTH), 32 + 7 * 18,
                   submitWidth, buttonHeight)) {
            shouldSubmit = true;
        }
    }

  private:
    void getInitials(char *c, int x, int y) {
        int change = 0;
        if (button("", x, y - 14, initialsWidth, 10))
            change = 1;
        LCD.WriteAt(*c, x + 1, y);
        if (button("", x, y + 19, initialsWidth, 10))
            change = -1;
        *c += change;
        if (*c > 'Z') {
            *c = 'A';
        }
        if (*c < 'A') {
            *c = 'Z';
        }
    }

    array<char, 3> initials{'A', 'A', 'A'};

    int player;
    int centerInitialX = center(initialsWidth, LCD_WIDTH);
    int numberOfShots;

    static const int initialsWidth = 16;
    static const int initialsHeight = 24;
    static const int initialsSpacing = 20;

    Statistics *statistics;

    bool shouldSubmit = false;
};