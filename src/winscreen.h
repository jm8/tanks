#include "common.h"
#include "gamestate.h"
#include "tank.h"
#include <FEHLCD.h>
#include <array>
#include <sstream>

class WinScreen : public GameState {

  public:
    WinScreen(int player, int numberOfShots)
        : player(player), numberOfShots(numberOfShots) {
    }

    SwitchStateAction update(double dt) {
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

        array<char, 3> initials{'A', 'A', 'A'};

        int centerInitialX = center(initialsWidth, LCD_WIDTH);
        int initialsY = 32 + 5 * 18;
        getInitials(&initials[0], centerInitialX - initialsSpacing, initialsY);
        getInitials(&initials[1], centerInitialX, initialsY);
        getInitials(&initials[2], centerInitialX + initialsSpacing, initialsY);
    }

  private:
    void getInitials(char *c, int x, int y) {
        button("", x, y - 14, initialsWidth, 10);
        LCD.WriteAt(*c, x, y);
    }

    int player;
    int centerInitialX = center(initialsWidth, LCD_WIDTH);
    int numberOfShots;

    static const int initialsWidth = 16;
    static const int initialsHeight = 24;
    static const int initialsSpacing = 18;
};