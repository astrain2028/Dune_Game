#include "Item.h"
#include <iostream>

Item::Item() {
    name = "";
    type = "";
    melangeValue = 0;
    bundleItem = false;
    stillSuitIntegrity = 0;
}

Item::Item(std::string itemName, std::string itemType, int itemMelangeValue, bool itemBundleItem, double itemStillSuitIntegrity) {
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
    if (bundleItem) {
        return melangeValue * 2; // If it's a bundle item, double the melange value
    }
    else {
        return melangeValue; // Otherwise, return the original melange value
    }
}

bool Item::isBundleItem(){
    return bundleItem;
}

double Item::calculateStillSuitIntegrity(){
    if (type == "Water") {
        return stillSuitIntegrity * 1.5; // If the item is water, increase the still suit integrity by 50%
    }
    else {
        return stillSuitIntegrity; // Otherwise, return the original still suit integrity
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
