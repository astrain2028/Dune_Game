#ifndef HARKONNEN_CHARACTER_H
#define HARKONNEN_CHARACTER_H
#include "Character.h"
#include <string>

class HarkonnenCharacter : public Character {
    private:
        int betrayalIncrease;       // how much Betrayal goes up when Dr. Strain deals with them
        int shortcutCost;           // how much spice the shortcut costs
        std::string shortcutItem;   // the bundle item they are offering as a shortcut
        bool dealtWith;             // tracks whether Dr. Strain has already taken their shortcut
    public:
        HarkonnenCharacter();
        HarkonnenCharacter(std::string name, std::string location, int friendship,
                           int betrayalIncrease, int shortcutCost, std::string shortcutItem);
        int getBetrayalIncrease();      // returns betrayalIncrease
        int getShortcutCost();          // returns shortcutCost
        std::string getShortcutItem();  // returns shortcutItem
        bool hasDealtWith();            // returns dealtWith
        void offerShortcut();           // prints their dialogue and shortcut offer to the screen
        void acceptShortcut();          // sets dealtWith to true and prints a confirmation message
};

#endif
