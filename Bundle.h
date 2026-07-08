#ifndef BUNDLE_H
#define BUNDLE_H
#include <string>
#include "Item.h"

const int BUNDLE_SIZE = 5;

class Bundle {
    private:
        Item requiredItems[BUNDLE_SIZE];    // the 5 habitat components the shelter needs
        bool donated[BUNDLE_SIZE];          // parallel array tracking which have been donated
    public:
        Bundle();
        bool isItemNeeded(std::string itemName);    // required and not yet donated
        bool donateItem(Item item);                 // marks the item donated, returns false if not needed
        bool isComplete();                          // true when all 5 components are donated
        int getDonatedCount();
        void displayProgress();                     // prints a checklist of the shelter's needs
};

#endif
