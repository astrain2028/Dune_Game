#include "Bundle.h"
#include <iostream>

Bundle::Bundle() {
    // Constructor: define the five components the shelter needs
    requiredItems[0] = Item("Spice Melange", "Spice", 50, true, 0);
    requiredItems[1] = Item("Water Cache", "Water", 30, true, 0);
    requiredItems[2] = Item("Atomics", "Weapon", 100, true, 0);
    requiredItems[3] = Item("Shield Generator Component", "Technology", 60, true, 0);
    requiredItems[4] = Item("Crysknife", "Weapon", 40, true, 0);
    for (int i = 0; i < BUNDLE_SIZE; i++) {
        donated[i] = false;
    }
}

bool Bundle::isItemNeeded(std::string itemName) {
    for (int i = 0; i < BUNDLE_SIZE; i++) {
        if (requiredItems[i].getName() == itemName) {
            return !donated[i];
        }
    }
    return false;
}

bool Bundle::donateItem(Item item) {
    for (int i = 0; i < BUNDLE_SIZE; i++) {
        if (requiredItems[i].getName() == item.getName()) {
            // Validation Policy: each component can only be donated once
            if (donated[i]) {
                std::cout << "The shelter already has a " << item.getName() << "." << std::endl;
                return false;
            }
            donated[i] = true;
            std::cout << ">>> " << item.getName() << " donated to the Fremen shelter! ("
                      << getDonatedCount() << "/" << BUNDLE_SIZE << ")" << std::endl;
            return true;
        }
    }
    std::cout << "The shelter has no need of a " << item.getName() << "." << std::endl;
    return false;
}

bool Bundle::isComplete() {
    for (int i = 0; i < BUNDLE_SIZE; i++) {
        if (!donated[i]) {
            return false;
        }
    }
    return true;
}

int Bundle::getDonatedCount() {
    int count = 0;
    for (int i = 0; i < BUNDLE_SIZE; i++) {
        if (donated[i]) {
            count++;
        }
    }
    return count;
}

void Bundle::displayProgress() {
    std::cout << "Fremen Shelter (" << getDonatedCount() << "/" << BUNDLE_SIZE
              << " components donated):" << std::endl;
    for (int i = 0; i < BUNDLE_SIZE; i++) {
        if (donated[i]) {
            std::cout << "  [X] " << requiredItems[i].getName() << std::endl;
        } else {
            std::cout << "  [ ] " << requiredItems[i].getName() << std::endl;
        }
    }
}
