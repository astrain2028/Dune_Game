#include "Player.h"
#include <iostream>

Player::Player() {
    // Default constructor
    currentDay = 1;
    stillsuitIntegrity = 100;
    spice = 0;
    inventorySize = 0;
    betrayal = 0;
    actionsRemaining = 0;
}

Player::Player(std::string playerName, int startingSpice, std::string startLocation, int actionsPerDay) {
    // Constructor
    name = playerName;
    currentDay = 1;
    stillsuitIntegrity = 100;
    spice = startingSpice;
    currentLocation = startLocation;
    inventorySize = 0;
    betrayal = 0;
    actionsRemaining = actionsPerDay;
}

std::string Player::getName() {
    return name;
}

int Player::getCurrentDay() {
    return currentDay;
}

int Player::getStillsuitIntegrity() {
    return stillsuitIntegrity;
}

int Player::getSpice() {
    return spice;
}

std::string Player::getCurrentLocation() {
    return currentLocation;
}

int Player::getInventorySize() {
    return inventorySize;
}

Item Player::getItem(int index) {
    if (index >= 0 && index < inventorySize) {
        return inventory[index];
    }
    return Item();
}

int Player::getBetrayal() {
    return betrayal;
}

int Player::getActionsRemaining() {
    return actionsRemaining;
}

void Player::moveTo(std::string locationName) {
    currentLocation = locationName;
}

bool Player::addItem(Item item) {
    // Validation Policy
    if (inventorySize >= MAX_INVENTORY) {
        return false;
    }
    inventory[inventorySize] = item;
    inventorySize++;
    return true;
}

bool Player::removeItem(std::string itemName) {
    for (int i = 0; i < inventorySize; i++) {
        if (inventory[i].getName() == itemName) {
            // shift everything after it left by one
            for (int j = i; j < inventorySize - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            inventorySize--;
            return true;
        }
    }
    return false;
}

bool Player::hasItem(std::string itemName) {
    for (int i = 0; i < inventorySize; i++) {
        if (inventory[i].getName() == itemName) {
            return true;
        }
    }
    return false;
}

bool Player::spendSpice(int amount) {
    // Validation Policy
    if (amount > spice) {
        return false;
    }
    spice = spice - amount;
    return true;
}

void Player::earnSpice(int amount) {
    spice = spice + amount;
}

void Player::degradeStillsuit(int amount) {
    stillsuitIntegrity = stillsuitIntegrity - amount;
    // Floor Policy: integrity cannot drop below zero
    if (stillsuitIntegrity < 0) {
        stillsuitIntegrity = 0;
    }
}

void Player::repairStillsuit(int amount) {
    stillsuitIntegrity = stillsuitIntegrity + amount;
    // Cap Policy: integrity cannot exceed 100
    if (stillsuitIntegrity > 100) {
        stillsuitIntegrity = 100;
    }
}

void Player::increaseBetrayal(int amount) {
    betrayal = betrayal + amount;
}

bool Player::useAction() {
    // Validation Policy
    if (actionsRemaining <= 0) {
        return false;
    }
    actionsRemaining--;
    return true;
}

void Player::advanceDay(int actionsPerDay) {
    currentDay++;
    actionsRemaining = actionsPerDay;
}

void Player::displayStats() {
    std::cout << "====== DR. AUSTIN STRAIN - FIELD LOG ======" << std::endl;
    std::cout << "Day:       " << currentDay << std::endl;
    std::cout << "Location:  " << currentLocation << std::endl;
    std::cout << "Stillsuit: " << stillsuitIntegrity << " / 100" << std::endl;
    std::cout << "Spice:     " << spice << std::endl;
    std::cout << "Betrayal:  " << betrayal << " / 100" << std::endl;
    std::cout << "Actions:   " << actionsRemaining << " remaining today" << std::endl;
    std::cout << "Inventory (" << inventorySize << "/" << MAX_INVENTORY << "):" << std::endl;
    if (inventorySize == 0) {
        std::cout << " - (empty)" << std::endl;
    }
    for (int i = 0; i < inventorySize; i++) {
        inventory[i].displayInfo();
    }
}
