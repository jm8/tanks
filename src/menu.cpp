#include "src/menu.h"
#include "game.h"
#include "gamestate.h"
#include "src/common.h"
#include "src/statistics.h"
#include <FEHLCD.h>
#include <iostream>

using namespace std;

const vector<string> INSTRUCTIONS{
    "TANKS is a 2 player game.",
    "Goal: destroy the",
    "other tank with 3",
    "perfectly aimed shots.",
    "",
    "Aim with the mouse and",
    "click to shoot.",
    "Gravity and random wind",
    "affect the projectile.",

};

const vector<string> CREDITS{
    "Created by:",
    "Joshua Sims",
    "Dennis Zhitenev",
};

// Switch state if the play button was pressed
// written by Josh
SwitchStateAction Menu::update(double dt) {
    return playPressed ? SWITCH_STATE_GOTO_GAME : SWITCH_STATE_STAY;
}

void Menu::draw() {
    LCD.Clear(SKY_COLOR);
    LCD.SetFontColor(WHITE);
    int oldState = state;
    switch (oldState) {
    case STATE_MAIN_MENU: {
        // Main menu
        // Title
        LCD.WriteAt(name, center(strlen(name) * CHAR_WIDTH, LCD_WIDTH), 32);
        int topButton = 64;
        int buttonSpace = buttonHeight + 8;
        // Buttons
        if (button("Play", center(buttonWidth, LCD_WIDTH),
                   topButton + buttonSpace * 0, buttonWidth, buttonHeight)) {
            playPressed = true;
        };
        if (button("Statistics", center(buttonWidth, LCD_WIDTH),
                   topButton + buttonSpace * 1, buttonWidth, buttonHeight)) {
            state = STATE_STATISTICS;
        };
        if (button("Instructions", center(buttonWidth, LCD_WIDTH),
                   topButton + buttonSpace * 2, buttonWidth, buttonHeight)) {
            state = STATE_INSTRUCTIONS;
        };
        if (button("Credits", center(buttonWidth, LCD_WIDTH),
                   topButton + buttonSpace * 3, buttonWidth, buttonHeight)) {
            state = STATE_CREDITS;
        };
        break;
    }
    case STATE_INSTRUCTIONS:
        // Instructions
        writeStrings(INSTRUCTIONS);
        break;
    case STATE_CREDITS:
        // Credits
        writeStrings(CREDITS);
        break;
    case STATE_STATISTICS: {
        // Leaderboard
        vector<Statistic> topTen = statistics->topTen();
        writeStrings({"TOP 10 by fewest shots"});
        for (int i = 0; i < topTen.size(); i++) {
            LCD.WriteAt(topTen[i].to_string().c_str(), 16, 16 + 18 * (i + 2));
        }
    } break;
    default:
        break;
    }
    if (oldState != STATE_MAIN_MENU) {
        // Back button
        int margin = 16;
        int backButtonWidth = 16 * 6;
        if (button("Back", LCD_WIDTH - backButtonWidth - margin,
                   LCD_HEIGHT - buttonHeight - margin, backButtonWidth,
                   buttonHeight)) {
            state = STATE_MAIN_MENU;
        }
    }
}

// Write a bunch of strings to the screen (for instructions and credits).
void Menu::writeStrings(vector<string> strings) {
    for (int i = 0; i < strings.size(); i++) {
        LCD.WriteAt(strings[i].c_str(), 16, 16 + 18 * i);
    }
}
