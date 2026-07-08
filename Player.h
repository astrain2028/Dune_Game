#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Item.h"

const int MAX_INVENTORY = 10;

class Player {
    private:
        std::string name;
        int currentDay;
        int stillsuitIntegrity;         // 0-100, reaching 0 means death on Arrakis
        int spice;                      // currency used for quests and shortcuts
        std::string currentLocation;
        Item inventory[MAX_INVENTORY];
        int inventorySize;
        int betrayal;                   // rises when dealing with Harkonnens or the Imperium
        int actionsRemaining;           // actions left today
    public:
        Player();
        Player(std::string name, int startingSpice, std::string startLocation, int actionsPerDay);
        std::string getName();
        int getCurrentDay();
        int getStillsuitIntegrity();
        int getSpice();
        std::string getCurrentLocation();
        int getInventorySize();
        Item getItem(int index);
        int getBetrayal();
        int getActionsRemaining();

        void moveTo(std::string locationName);
        bool addItem(Item item);            // returns false if the inventory is full
        bool removeItem(std::string itemName);
        bool hasItem(std::string itemName);
        bool spendSpice(int amount);        // returns false if the player cannot afford it
        void earnSpice(int amount);
        void degradeStillsuit(int amount);  // never drops below 0
        void repairStillsuit(int amount);   // never rises above 100
        void increaseBetrayal(int amount);
        bool useAction();                   // returns false if no actions remain
        void advanceDay(int actionsPerDay); // next day, refresh actions
        void displayStats();
};

#endif
