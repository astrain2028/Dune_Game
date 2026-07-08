#ifndef LOCATION_H
#define LOCATION_H
#include <string>

const int MAX_CONNECTIONS = 4;

class Location {
    private:
        std::string name;
        std::string description;
        bool unlocked;                              // locked locations must be unlocked by an Atreides ally
        std::string connections[MAX_CONNECTIONS];   // names of directly connected locations (for BFS)
        int numConnections;
        int spiceYield;                             // spice gained each time the player searches here
        std::string hiddenItemName;                 // item hidden here ("" if none)
        bool itemFound;                             // whether the hidden item has been found
    public:
        Location();
        Location(std::string name, std::string description, bool unlocked,
                 int spiceYield, std::string hiddenItemName);
        std::string getName();
        std::string getDescription();
        bool isUnlocked();
        int getSpiceYield();
        int getNumConnections();
        std::string getConnection(int index);   // provides connections to the BFS pathfinder
        void addConnection(std::string locationName);
        void unlock();
        void displayInfo();                     // prints name, lock status, and connections
        bool hasHiddenItem();                   // true if an item is still hidden here
        std::string findHiddenItem();           // returns the item name and marks it found
};

#endif
