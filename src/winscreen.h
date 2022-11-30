#include "gamestate.h"
#include "common.h"
#include "tank.h"
#include <FEHLCD.h>
#include <sstream>

class WinScreen : public GameState {

  public:
    WinScreen(int player, int numberOfShots) : player(player), numberOfShots(numberOfShots) {}

    SwitchStateAction update(double dt) {
        return SWITCH_STATE_STAY;
    }

    void draw() {
        LCD.Clear(SKY_COLOR);
        
        const char *congrats = player == LEFT ? "LEFT PLAYER WINS!" : "RIGHT PLAYER WINS!";
        LCD.SetFontColor(WHITE);
        LCD.WriteAt(congrats, center(strlen(congrats)*CHAR_WIDTH, LCD_WIDTH), 32);
        
        LCD.SetFontColor(WHITE);
        ostringstream ss;
        ss << "It took " << numberOfShots << " shots";
        LCD.WriteAt(ss.str().c_str(), center(ss.str().size()*CHAR_WIDTH, LCD_WIDTH), 32+18);

        const char *enterYourInitials = "Enter your initials:";
        LCD.WriteAt(enterYourInitials, center(strlen(enterYourInitials)*CHAR_WIDTH, LCD_WIDTH), 32+2*18);

        
    }

  private:
    int player;
    int numberOfShots;
};