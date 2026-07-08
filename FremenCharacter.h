#ifndef FREMEN_CHARACTER_H
#define FREMEN_CHARACTER_H
#include "Character.h"
#include <string>

class FremenCharacter : public Character {
    private:
        int repairAmount;       // how much stillsuit integrity they can restore
        bool willingToHelp;     // false once Dr. Strain's betrayals become known
        int spiceToProvide;     // how much spice they can source for Dr. Strain
        bool spiceGiven;        // whether they have already sourced spice
        int questSpiceCost;     // spice Dr. Strain must offer to complete their quest
    public:
        FremenCharacter();
        FremenCharacter(std::string name, std::string location, int friendship,
                        std::string questDescription, std::string questReward,
                        int questSpiceCost, int repairAmount, int spiceToProvide);
        int getRepairAmount();
        bool isWillingToHelp();
        int getQuestSpiceCost();
        void updateWillingness(int betrayal);   // they refuse to help if betrayal is 50 or more
        int repairStillsuit(int betrayal);      // returns repair amount, reduced by betrayal
        int sourceSpice();                      // returns spiceToProvide once, then 0
        void offerQuest();                      // prints the quest, its cost, and its reward
};

#endif
