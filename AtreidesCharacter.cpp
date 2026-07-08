#include "AtreidesCharacter.h"
#include <iostream>

AtreidesCharacter::AtreidesCharacter() : Character() {
    // Default constructor
    hasUnlockedLocation = false;
}

AtreidesCharacter::AtreidesCharacter(std::string name, std::string location, int friendship,
                                     std::string hint, std::string unlockLocation)
    : Character(name, location, friendship, "", "") {
    // Constructor
    // Atreides characters give hints, not quests, so the base class's
    // quest description and reward are left blank.
    hintMessage = hint;
    locationToUnlock = unlockLocation;
    hasUnlockedLocation = false;
}

void AtreidesCharacter::giveHint() {
    std::cout << getName() << ": \"" << hintMessage << "\"" << std::endl;
}

std::string AtreidesCharacter::getLocationToUnlock() {
    return locationToUnlock;
}

bool AtreidesCharacter::hasUnlocked() {
    return hasUnlockedLocation;
}

void AtreidesCharacter::unlockLocation() {
    hasUnlockedLocation = true;
    std::cout << getName() << " marks the " << locationToUnlock
              << " on your map. You can now travel there." << std::endl;
}
