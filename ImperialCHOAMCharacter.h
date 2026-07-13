#ifndef IMPERIAL_CHOAM_CHARACTER_H
#define IMPERIAL_CHOAM_CHARACTER_H
#include "Character.h"
#include <string>

class ImperialCHOAMCharacter : public Character {
    private:
        int betrayalIncrease;       // how much Betrayal goes up per deal (higher than Harkonnen)
        std::string shortcutItem;   // the bundle item they are offering
        int shortcutCost;           // how much spice the shortcut costs
        bool betrayed;              // tracks whether Dr. Strain has taken their deal
    public:
        ImperialCHOAMCharacter();
        ImperialCHOAMCharacter(std::string name, std::string location, int friendship,
                               int betrayalIncrease, int shortcutCost, std::string shortcutItem);
        int getBetrayalIncrease();
        std::string getShortcutItem();
        int getShortcutCost();
        bool hasBetrayed();
        void offerDeal();       // prints their dialogue and what they are offering
        void acceptDeal();      // sets betrayed to true, prints confirmation
        void displayStatus();   // confirms the deal is concluded
};

#endif
