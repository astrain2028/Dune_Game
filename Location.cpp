#include "Location.h"
#include <iostream>

Location::Location() {
    // Default constructor
    unlocked = true;
    numConnections = 0;
    spiceYield = 0;
    itemFound = false;
}

Location::Location(std::string locationName, std::string locationDescription, bool startsUnlocked,
                   int locationSpiceYield, std::string hiddenItem) {
    // Constructor
    name = locationName;
    description = locationDescription;
    unlocked = startsUnlocked;
    numConnections = 0;
    spiceYield = locationSpiceYield;
    hiddenItemName = hiddenItem;
    itemFound = false;
}

std::string Location::getName() {
    return name;
}

std::string Location::getDescription() {
    return description;
}

bool Location::isUnlocked() {
    return unlocked;
}

int Location::getSpiceYield() {
    return spiceYield;
}

int Location::getNumConnections() {
    return numConnections;
}

std::string Location::getConnection(int index) {
    if (index >= 0 && index < numConnections) {
        return connections[index];
    }
    return "";
}

void Location::addConnection(std::string locationName) {
    // Validation Policy
    if (numConnections < MAX_CONNECTIONS) {
        connections[numConnections] = locationName;
        numConnections++;
    }
}

void Location::unlock() {
    unlocked = true;
}

void Location::displayInfo() {
    std::cout << " - " << name;
    if (!unlocked) {
        std::cout << " [LOCKED]";
    }
    std::cout << std::endl << "     connects to: ";
    for (int i = 0; i < numConnections; i++) {
        std::cout << connections[i];
        if (i < numConnections - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

bool Location::hasHiddenItem() {
    return hiddenItemName != "" && !itemFound;
}

std::string Location::findHiddenItem() {
    if (hasHiddenItem()) {
        itemFound = true;
        return hiddenItemName;
    }
    return "";
}
