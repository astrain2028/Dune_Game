#ifndef ATREIDES_CHARACTER_H
#define ATREIDES_CHARACTER_H
#include "Character.h"
#include <string>

class AtreidesCharacter : public Character {
    private:
        std::string hintMessage;        // a piece of advice or information they share with Dr. Strain
        std::string locationToUnlock;   // the name of the location they can unlock for Dr. Strain
        bool hasUnlockedLocation;       // tracks whether they have already unlocked their location
    public:
        AtreidesCharacter();
        AtreidesCharacter(std::string name, std::string location, int friendship,
                          std::string hintMessage, std::string locationToUnlock);
        void giveHint();                    // prints the hintMessage to the screen
        std::string getLocationToUnlock();  // returns the location name
        bool hasUnlocked();                 // returns hasUnlockedLocation
        void unlockLocation();              // sets hasUnlockedLocation to true and prints a message
};

#endif
