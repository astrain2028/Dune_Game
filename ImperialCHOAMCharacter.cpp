#include "ImperialCHOAMCharacter.h"
#include <iostream>

ImperialCHOAMCharacter::ImperialCHOAMCharacter() : Character() {
    // Default constructor
    betrayalIncrease = 0;
    shortcutCost = 0;
    betrayed = false;
}

ImperialCHOAMCharacter::ImperialCHOAMCharacter(std::string name, std::string location, int friendship,
                                               int betrayal, int cost, std::string item)
    : Character(name, location, friendship, "", "") {
    // Constructor
    // The Emperor and CHOAM sell deals, not quests, so the base class's
    // quest description and reward are left blank.
    betrayalIncrease = betrayal;
    shortcutItem = item;
    shortcutCost = cost;
    betrayed = false;
}

int ImperialCHOAMCharacter::getBetrayalIncrease() {
    return betrayalIncrease;
}

std::string ImperialCHOAMCharacter::getShortcutItem() {
    return shortcutItem;
}

int ImperialCHOAMCharacter::getShortcutCost() {
    return shortcutCost;
}

bool ImperialCHOAMCharacter::hasBetrayed() {
    return betrayed;
}

void ImperialCHOAMCharacter::offerDeal() {
    std::cout << getName() << ": \"The Imperium rewards cooperation, Dr. Strain. A "
              << shortcutItem << " can be arranged for a mere " << shortcutCost
              << " spice. The Fremen need never know.\"" << std::endl;
}

void ImperialCHOAMCharacter::acceptDeal() {
    betrayed = true;
    std::cout << getName() << ": \"Excellent. Consider it done. The Imperium does not forget "
              << "its... friends.\"" << std::endl;
}

void ImperialCHOAMCharacter::displayStatus() {
    std::cout << getName() << " considers your dealings concluded, Doctor." << std::endl;
}
