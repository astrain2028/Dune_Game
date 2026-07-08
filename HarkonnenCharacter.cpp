#include "HarkonnenCharacter.h"
#include <iostream>

HarkonnenCharacter::HarkonnenCharacter() : Character() {
    betrayalIncrease = 0;
    shortcutCost = 0;
    shortcutItem = "";
    dealtWith = false;
}

HarkonnenCharacter::HarkonnenCharacter(std::string name, std::string location, int friendship,
                                       int betrayal, int cost, std::string item)
    : Character(name, location, friendship, "", "") {
    betrayalIncrease = betrayal;
    shortcutCost = cost;
    shortcutItem = item;
    dealtWith = false;
}

int HarkonnenCharacter::getBetrayalIncrease() {
    return betrayalIncrease;
}

int HarkonnenCharacter::getShortcutCost() {
    return shortcutCost;
}

std::string HarkonnenCharacter::getShortcutItem() {
    return shortcutItem;
}

bool HarkonnenCharacter::hasDealtWith() {
    return dealtWith;
}

void HarkonnenCharacter::offerShortcut() {
    std::cout << getName() << ": \"No need to grovel in the sand, doctor. I can get you a "
              << shortcutItem << " today... for " << shortcutCost << " spice.\"" << std::endl;
}

void HarkonnenCharacter::acceptShortcut() {
    dealtWith = true;
    std::cout << getName() << ": \"A wise choice. The Harkonnens always deliver... "
              << "and always remember who owes them.\"" << std::endl;
}
