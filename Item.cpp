#include "Item.h"
#include <iostream>

Item::Item() {
    // Default constructor
    melangeValue = 0;
    bundleItem = false;
    stillSuitIntegrity = 0;
}

Item::Item(std::string itemName, std::string itemType, int itemMelangeValue, bool itemBundleItem, double itemStillSuitIntegrity) {
    // Constructor
    name = itemName;
    type = itemType;
    melangeValue = itemMelangeValue;
    bundleItem = itemBundleItem;
    stillSuitIntegrity = itemStillSuitIntegrity;
}

std::string Item::getName(){
    return name;
}

std::string Item::getType(){
    return type;
}

int Item::calculateMelangeValue(){
    // Bonus Policy: bundle items are worth double
    if (bundleItem) {
        return melangeValue * 2;
    }
    else {
        return melangeValue;
    }
}

bool Item::isBundleItem(){
    return bundleItem;
}

double Item::calculateStillSuitIntegrity(){
    // Bonus Policy: water items restore 50% more integrity
    if (type == "Water") {
        return stillSuitIntegrity * 1.5;
    }
    else {
        return stillSuitIntegrity;
    }
}

void Item::displayInfo(){
    std::cout << " - " << name << " (" << type << ")";
    if (bundleItem) {
        std::cout << " [habitat component]";
    }
    if (calculateStillSuitIntegrity() > 0) {
        std::cout << " [restores " << calculateStillSuitIntegrity() << " stillsuit integrity]";
    }
    std::cout << std::endl;
}
