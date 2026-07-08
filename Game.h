#ifndef GAME_H
#define GAME_H
#include <string>
#include "Player.h"
#include "FremenCharacter.h"
#include "HarkonnenCharacter.h"
#include "AtreidesCharacter.h"
#include "ImperialCHOAMCharacter.h"
#include "Bundle.h"
#include "Location.h"
#include "Item.h"

const int NUM_LOCATIONS = 6;

class Game {
    private:
        Player player;                          // Dr. Austin Strain
        FremenCharacter fremenChars[3];         // Chani, Stilgar, Shai-Hulud
        HarkonnenCharacter harkChars[3];        // Feyd-Rautha, Rabban, the Baron
        AtreidesCharacter atreidesChars[3];     // Paul, Jessica, Gurney
        ImperialCHOAMCharacter imperialChars[2];// Emperor and CHOAM Representative
        Bundle bundle;                          // the habitat components tracker
        Location locations[NUM_LOCATIONS];      // all 6 locations on Arrakis
        bool gameOver;
        bool playerWon;
        std::string lossReason;

        // helpers
        int readMenuChoice(int minChoice, int maxChoice);
        bool askYesNo();
        int findLocationIndex(std::string locationName);
        int findPathBFS(int startIndex, int destIndex, int path[]);  // returns # of legs, -1 if unreachable
        Item makeItem(std::string itemName);
        bool requireAction();
        void talkToAtreides(int index);
        void talkToFremen(int index);
        void talkToHarkonnen(int index);
        void talkToImperial(int index);
        void useItem();
        void donateComponents();
    public:
        Game();
        void startGame();
        void gameLoop();
        void displayDashboard();
        void displayMap();
        void showMainMenu();
        void processChoice(int choice);
        void movePlayer();
        void talkToCharacter();
        void visitLocation();
        void endDay();
        bool checkWin();
        bool checkLoss();
        void displayEnding();
};

#endif
