#ifndef ITEM_H
#define ITEM_H
#include <string>


class Item {
private:
    std::string name;
    std::string type;
    int melangeValue;
    bool bundleItem;
    double stillSuitIntegrity;
public:
    Item();
    Item(std::string name, std::string type, int melangeValue, bool bundleItem, double stillSuitIntegrity);

    std::string getName();
    std::string getType();
    int calculateMelangeValue();
    bool isBundleItem();
    double calculateStillSuitIntegrity();
    void displayInfo();
};




#endif
