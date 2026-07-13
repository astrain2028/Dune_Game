#include "Bundle.h"
#include <iostream>
#include <fstream>

Bundle::Bundle() {
    // Constructor: define the five components the shelter needs
    loadRequiredItems();
    for (int i = 0; i < BUNDLE_SIZE; i++) {
        donated[i] = false;
    }
}

void Bundle::loadRequiredItems() {
    std::ifstream file("items.txt");
    if (!file.is_open()) {
        // Fallback Policy: use these defaults if items.txt is missing
        requiredItems[0] = Item("Spice Melange", "Spice", 50, true, 0);
        requiredItems[1] = Item("Water Cache", "Water", 30, true, 0);
        requiredItems[2] = Item("Atomics", "Weapon", 100, true, 0);
        requiredItems[3] = Item("Shield Generator Component", "Technology", 60, true, 0);
        requiredItems[4] = Item("Crysknife", "Weapon", 40, true, 0);
        return;
    }

    std::string line;
    int index = 0;
    while (getline(file, line) && index < BUNDLE_SIZE) {
        // Each line looks like: name,type,melangeValue
        int firstComma = line.find(',');
        int secondComma = line.find(',', firstComma + 1);
        std::string itemName = line.substr(0, firstComma);
        std::string itemType = line.substr(firstComma + 1, secondComma - firstComma - 1);
        std::string valueText = line.substr(secondComma + 1);

        // Manually convert the value text to an int, ignoring any stray characters
        int itemValue = 0;
        int valueLength = valueText.length();
        for (int i = 0; i < valueLength; i++) {
            if (valueText[i] >= '0' && valueText[i] <= '9') {
                itemValue = itemValue * 10 + (valueText[i] - '0');
            }
        }

        requiredItems[index] = Item(itemName, itemType, itemValue, true, 0);
        index++;
    }
    file.close();
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
