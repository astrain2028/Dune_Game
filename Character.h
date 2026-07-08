#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>

class Character {
    private:
        std::string name;
        std::string location;
        int friendship;
        std::string questDescription;
        bool questComplete;
        std::string questReward;
    public:
        Character();
        Character(std::string name, std::string location, int friendship,
                  std::string questDescription, std::string questReward);
        std::string getName();
        std::string getLocation();
        int getFriendship();
        std::string getQuestDescription();
        bool isQuestCompleted();
        int increaseFriendship(int amount);
        void completeQuest();
        std::string getQuestReward();
        void displayDialogue();

};

#endif
