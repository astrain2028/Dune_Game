#include "FremenCharacter.h"
#include <iostream>

FremenCharacter::FremenCharacter() : Character() {
    repairAmount = 0;
    willingToHelp = true;
    spiceToProvide = 0;
    spiceGiven = false;
    questSpiceCost = 0;
}

FremenCharacter::FremenCharacter(std::string name, std::string location, int friendship,
                                 std::string questDescription, std::string questReward,
                                 int spiceCost, int repair, int spiceGift)
    : Character(name, location, friendship, questDescription, questReward) {
    repairAmount = repair;
    willingToHelp = true;
    spiceToProvide = spiceGift;
    spiceGiven = false;
    questSpiceCost = spiceCost;
}

int FremenCharacter::getRepairAmount() {
    return repairAmount;
}

bool FremenCharacter::isWillingToHelp() {
    return willingToHelp;
}

int FremenCharacter::getQuestSpiceCost() {
    return questSpiceCost;
}

void FremenCharacter::updateWillingness(int betrayal) {
    willingToHelp = betrayal < 50;
}

int FremenCharacter::repairStillsuit(int betrayal) {
    if (!willingToHelp || betrayal >= 50) {
        return 0;
    }
    // the more Dr. Strain has betrayed the Fremen, the less care they take
    int amount = repairAmount - betrayal / 2;
    if (amount < 10) {
        amount = 10;
    }
    return amount;
}

int FremenCharacter::sourceSpice() {
    if (spiceGiven || !willingToHelp) {
        return 0;
    }
    spiceGiven = true;
    return spiceToProvide;
}

void FremenCharacter::offerQuest() {
    std::cout << getName() << ": \"" << getQuestDescription() << "\"" << std::endl;
    std::cout << "  Cost: " << questSpiceCost << " spice" << std::endl;
    std::cout << "  Reward: " << getQuestReward() << std::endl;
}
