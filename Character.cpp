#include "Character.h"
#include <iostream>


Character::Character() {
    // Default constructor
    friendship = 0;
    questComplete = false;
}

Character::Character(std::string characterName, std::string characterLocation, int characterFriendship,
                     std::string characterQuestDescription, std::string characterQuestReward) {
    // Constructor
    name = characterName;
    location = characterLocation;
    friendship = characterFriendship;
    questDescription = characterQuestDescription;
    questComplete = false;
    questReward = characterQuestReward;
}

std::string Character::getName() {
    return name;
}

std::string Character::getLocation() {
    return location;
}

int Character::getFriendship() {
    return friendship;
}

std::string Character::getQuestDescription() {
    return questDescription;
}

bool Character::isQuestCompleted() {
    return questComplete;
}

int Character::increaseFriendship(int amount) {
    friendship += amount;
    // Cap Policy: friendship cannot exceed 100
    if (friendship > 100) {
        friendship = 100;
    }
    return friendship;
}

void Character::completeQuest() {
    questComplete = true;
}

std::string Character::getQuestReward() {
    return questReward;
}

void Character::displayDialogue() {
    std::cout << "Hello, I am " << name << " of " << location << "." << std::endl;
}
