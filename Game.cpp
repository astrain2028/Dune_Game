#include "Game.h"
#include <iostream>

const int MAX_DAYS = 10;
const int ACTIONS_PER_DAY = 4;
const int MAX_BETRAYAL = 100;
const int TRAVEL_WEAR_PER_LEG = 3;
const int SEARCH_WEAR = 5;
const int NIGHT_WEAR = 5;

Game::Game() {
    player = Player("Dr. Austin Strain", 20, "Research Outpost", ACTIONS_PER_DAY);
    gameOver = false;
    playerWon = false;
    lossReason = "";

    locations[0] = Location("Research Outpost",
        "Your battered field lab. Sand hisses against the shutters.",
        true, 0, "Shield Generator Component");
    locations[1] = Location("Arrakeen",
        "The capital city of Arrakis. Dusty streets bustle beneath shield walls.",
        true, 5, "");
    locations[2] = Location("Sietch Tabr",
        "A hidden Fremen stronghold carved into the rock. The shelter is being built here.",
        true, 0, "Literjon of Water");
    locations[3] = Location("Harkonnen Outpost",
        "A brutal industrial fortress. Smoke and cruelty hang in the air.",
        false, 5, "Atomics");
    locations[4] = Location("Emperor's Palace",
        "A gilded outpost of the Imperium, far above the sand and the sweat.",
        false, 0, "");
    locations[5] = Location("Sandworm Fields",
        "Endless dunes where the great makers roam. The drumming of the sand calls them.",
        false, 15, "Spice Melange");

    // the travel graph of Arrakis (used by the BFS pathfinder)
    locations[0].addConnection("Arrakeen");
    locations[0].addConnection("Sandworm Fields");
    locations[1].addConnection("Research Outpost");
    locations[1].addConnection("Sietch Tabr");
    locations[1].addConnection("Harkonnen Outpost");
    locations[1].addConnection("Emperor's Palace");
    locations[2].addConnection("Arrakeen");
    locations[2].addConnection("Sandworm Fields");
    locations[3].addConnection("Arrakeen");
    locations[3].addConnection("Emperor's Palace");
    locations[4].addConnection("Arrakeen");
    locations[4].addConnection("Harkonnen Outpost");
    locations[5].addConnection("Research Outpost");
    locations[5].addConnection("Sietch Tabr");

    atreidesChars[0] = AtreidesCharacter("Paul Atreides", "Arrakeen", 50,
        "The makers guard the richest spice sands. Walk without rhythm and the Sandworm Fields are yours.",
        "Sandworm Fields");
    atreidesChars[1] = AtreidesCharacter("Lady Jessica", "Arrakeen", 40,
        "The Emperor and CHOAM will trade with anyone... but every deal has a hidden price.",
        "Emperor's Palace");
    atreidesChars[2] = AtreidesCharacter("Gurney Halleck", "Research Outpost", 30,
        "The Harkonnens hoard stolen atomics at their outpost. Search it well, if you dare go.",
        "Harkonnen Outpost");

    fremenChars[0] = FremenCharacter("Chani", "Sietch Tabr", 20,
        "Offer 15 spice to the sietch and our water sellers will part with a water cache.",
        "Water Cache", 15, 30, 10);
    fremenChars[1] = FremenCharacter("Stilgar", "Sietch Tabr", 10,
        "Prove your worth with 20 spice and the sietch will share its stores of melange.",
        "Spice Melange", 20, 40, 15);
    fremenChars[2] = FremenCharacter("Shai-Hulud", "Sandworm Fields", 0,
        "The maker rumbles beneath you. An offering of 25 spice to the desert may earn a tooth of the great worm.",
        "Crysknife", 25, 20, 25);

    harkChars[0] = HarkonnenCharacter("Feyd-Rautha", "Harkonnen Outpost", 0, 20, 25, "Water Cache");
    harkChars[1] = HarkonnenCharacter("Glossu Rabban", "Harkonnen Outpost", 0, 20, 25, "Spice Melange");
    harkChars[2] = HarkonnenCharacter("Baron Harkonnen", "Harkonnen Outpost", 0, 20, 30, "Crysknife");

    imperialChars[0] = ImperialCHOAMCharacter("Emperor Shaddam IV", "Emperor's Palace", 0,
                                              30, 40, "Atomics");
    imperialChars[1] = ImperialCHOAMCharacter("CHOAM Representative", "Emperor's Palace", 0,
                                              30, 40, "Shield Generator Component");
}

int Game::readMenuChoice(int minChoice, int maxChoice) {
    int choice;
    while (true) {
        std::cout << "> ";
        if (std::cin >> choice && choice >= minChoice && choice <= maxChoice) {
            return choice;
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n'); // discard the rest of the bad input line
        std::cout << "Please enter a number between " << minChoice << " and " << maxChoice << "." << std::endl;
    }
}

bool Game::askYesNo() {
    std::string answer;
    std::cout << "(y/n) > ";
    std::cin >> answer;
    return answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes";
}

int Game::findLocationIndex(std::string locationName) {
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        if (locations[i].getName() == locationName) {
            return i;
        }
    }
    return -1;
}

// Breadth-first search across unlocked locations. Fills path[] with location
// indices from start to destination and returns the number of legs, or -1 if
// no route exists.
int Game::findPathBFS(int startIndex, int destIndex, int path[]) {
    bool visited[NUM_LOCATIONS];
    int parent[NUM_LOCATIONS];
    int queue[NUM_LOCATIONS];
    int front = 0;
    int back = 0;

    for (int i = 0; i < NUM_LOCATIONS; i++) {
        visited[i] = false;
        parent[i] = -1;
    }
    queue[back] = startIndex;
    back++;
    visited[startIndex] = true;

    while (front < back) {
        int current = queue[front];
        front++;
        if (current == destIndex) {
            break;
        }
        for (int i = 0; i < locations[current].getNumConnections(); i++) {
            int next = findLocationIndex(locations[current].getConnection(i));
            if (next != -1 && !visited[next] && locations[next].isUnlocked()) {
                visited[next] = true;
                parent[next] = current;
                queue[back] = next;
                back++;
            }
        }
    }

    if (!visited[destIndex]) {
        return -1;
    }

    // walk back up the parent chain, then reverse it into path[]
    int reversed[NUM_LOCATIONS];
    int length = 0;
    int current = destIndex;
    while (current != -1) {
        reversed[length] = current;
        length++;
        current = parent[current];
    }
    for (int i = 0; i < length; i++) {
        path[i] = reversed[length - 1 - i];
    }
    return length - 1;
}

Item Game::makeItem(std::string itemName) {
    if (itemName == "Spice Melange") {
        return Item("Spice Melange", "Spice", 50, true, 0);
    }
    if (itemName == "Water Cache") {
        return Item("Water Cache", "Water", 30, true, 0);
    }
    if (itemName == "Atomics") {
        return Item("Atomics", "Weapon", 100, true, 0);
    }
    if (itemName == "Shield Generator Component") {
        return Item("Shield Generator Component", "Technology", 60, true, 0);
    }
    if (itemName == "Crysknife") {
        return Item("Crysknife", "Weapon", 40, true, 0);
    }
    if (itemName == "Literjon of Water") {
        return Item("Literjon of Water", "Water", 0, false, 20);
    }
    return Item();
}

bool Game::requireAction() {
    if (player.getActionsRemaining() <= 0) {
        std::cout << "You are exhausted. You must end the day before doing anything else." << std::endl;
        return false;
    }
    return true;
}

void Game::startGame() {
    std::cout << "==============================================" << std::endl;
    std::cout << "        DUNE: SHELTER FOR THE FREMEN          " << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "You are Dr. Austin Strain, a scientist stranded" << std::endl;
    std::cout << "on the desert planet Arrakis. The Fremen are" << std::endl;
    std::cout << "struggling to survive in the harsh desert." << std::endl;
    std::cout << std::endl;
    std::cout << "Collect five critical habitat components and" << std::endl;
    std::cout << "donate them at Sietch Tabr to power up a shelter" << std::endl;
    std::cout << "for the Fremen before your " << MAX_DAYS << "-day mission deadline:" << std::endl;
    std::cout << "  Spice Melange, a Water Cache, Atomics," << std::endl;
    std::cout << "  a Shield Generator Component, and a Crysknife." << std::endl;
    std::cout << std::endl;
    std::cout << "Find them, earn them, or buy them. But beware:" << std::endl;
    std::cout << "Harkonnen and Imperial shortcuts raise your" << std::endl;
    std::cout << "Betrayal. At 50 the Fremen stop helping you." << std::endl;
    std::cout << "At " << MAX_BETRAYAL << " you lose everything. And watch your" << std::endl;
    std::cout << "stillsuit - if it fails, the desert takes you." << std::endl;
    std::cout << std::endl;
    std::cout << "You have " << ACTIONS_PER_DAY << " actions per day. The spice must flow." << std::endl;
    gameLoop();
}

void Game::gameLoop() {
    while (!gameOver) {
        std::cout << std::endl;
        std::cout << "--- Day " << player.getCurrentDay() << " of " << MAX_DAYS
                  << " | " << player.getCurrentLocation()
                  << " | Stillsuit: " << player.getStillsuitIntegrity()
                  << " | Spice: " << player.getSpice()
                  << " | Actions: " << player.getActionsRemaining() << " ---" << std::endl;
        showMainMenu();
        int choice = readMenuChoice(1, 9);
        processChoice(choice);
        if (!gameOver) {
            if (checkWin()) {
                playerWon = true;
                gameOver = true;
            } else if (checkLoss()) {
                gameOver = true;
            }
        }
    }
    displayEnding();
}

void Game::showMainMenu() {
    std::cout << "1. View dashboard" << std::endl;
    std::cout << "2. View map" << std::endl;
    std::cout << "3. Travel (1 action)" << std::endl;
    std::cout << "4. Search this location (1 action)" << std::endl;
    std::cout << "5. Talk to someone here (1 action)" << std::endl;
    std::cout << "6. Use an item" << std::endl;
    std::cout << "7. Donate components to the shelter" << std::endl;
    std::cout << "8. End the day" << std::endl;
    std::cout << "9. Quit game" << std::endl;
}

void Game::processChoice(int choice) {
    if (choice == 1) {
        displayDashboard();
    } else if (choice == 2) {
        displayMap();
    } else if (choice == 3) {
        movePlayer();
    } else if (choice == 4) {
        visitLocation();
    } else if (choice == 5) {
        talkToCharacter();
    } else if (choice == 6) {
        useItem();
    } else if (choice == 7) {
        donateComponents();
    } else if (choice == 8) {
        endDay();
    } else if (choice == 9) {
        std::cout << "Abandon the mission and leave Arrakis?" << std::endl;
        if (askYesNo()) {
            lossReason = "quit";
            gameOver = true;
        }
    }
}

void Game::displayDashboard() {
    player.displayStats();
    bundle.displayProgress();
    std::cout << "===========================================" << std::endl;
}

void Game::displayMap() {
    std::cout << "============= MAP OF ARRAKIS =============" << std::endl;
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        if (locations[i].getName() == player.getCurrentLocation()) {
            std::cout << "*" ;
        } else {
            std::cout << " ";
        }
        locations[i].displayInfo();
    }
    std::cout << "(* = your current location)" << std::endl;
    std::cout << "==========================================" << std::endl;
}

void Game::movePlayer() {
    if (!requireAction()) {
        return;
    }
    std::cout << "Where will you travel? (1 action, stillsuit wears "
              << TRAVEL_WEAR_PER_LEG << " per leg)" << std::endl;
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        std::cout << i + 1 << ". " << locations[i].getName();
        if (!locations[i].isUnlocked()) {
            std::cout << " [LOCKED]";
        }
        if (locations[i].getName() == player.getCurrentLocation()) {
            std::cout << " (current)";
        }
        std::cout << std::endl;
    }
    std::cout << NUM_LOCATIONS + 1 << ". Stay where you are" << std::endl;
    int choice = readMenuChoice(1, NUM_LOCATIONS + 1);
    if (choice == NUM_LOCATIONS + 1) {
        return;
    }
    int destIndex = choice - 1;
    if (!locations[destIndex].isUnlocked()) {
        std::cout << "That location is locked. Perhaps an Atreides ally can help you." << std::endl;
        return;
    }
    if (locations[destIndex].getName() == player.getCurrentLocation()) {
        std::cout << "You are already there." << std::endl;
        return;
    }

    int startIndex = findLocationIndex(player.getCurrentLocation());
    int path[NUM_LOCATIONS];
    int legs = findPathBFS(startIndex, destIndex, path);
    if (legs == -1) {
        std::cout << "No safe route exists through the open desert." << std::endl;
        return;
    }

    std::cout << "Route: ";
    for (int i = 0; i <= legs; i++) {
        std::cout << locations[path[i]].getName();
        if (i < legs) {
            std::cout << " -> ";
        }
    }
    std::cout << " (" << legs << " leg(s))" << std::endl;

    player.useAction();
    player.degradeStillsuit(legs * TRAVEL_WEAR_PER_LEG);
    player.moveTo(locations[destIndex].getName());
    std::cout << "You arrive at " << locations[destIndex].getName()
              << ". (Stillsuit: " << player.getStillsuitIntegrity() << "/100)" << std::endl;
    std::cout << locations[destIndex].getDescription() << std::endl;
}

void Game::visitLocation() {
    if (!requireAction()) {
        return;
    }
    int li = findLocationIndex(player.getCurrentLocation());
    if (li == -1) {
        return;
    }
    player.useAction();
    player.degradeStillsuit(SEARCH_WEAR);
    std::cout << locations[li].getDescription() << std::endl;

    int spiceFound = locations[li].getSpiceYield();
    if (spiceFound > 0) {
        player.earnSpice(spiceFound);
        std::cout << "You harvest " << spiceFound << " spice. (Total: "
                  << player.getSpice() << ")" << std::endl;
    } else {
        std::cout << "You find no spice here." << std::endl;
    }

    if (locations[li].hasHiddenItem()) {
        if (player.getInventorySize() >= MAX_INVENTORY) {
            std::cout << "Something glints in the sand, but your pack is full!" << std::endl;
        } else {
            std::string itemName = locations[li].findHiddenItem();
            Item found = makeItem(itemName);
            player.addItem(found);
            std::cout << "Half-buried in the sand, you find: " << itemName << "!" << std::endl;
        }
    }
    std::cout << "(Stillsuit: " << player.getStillsuitIntegrity() << "/100)" << std::endl;
}

void Game::talkToCharacter() {
    if (!requireAction()) {
        return;
    }
    std::string current = player.getCurrentLocation();
    // faction codes: 0 = Atreides, 1 = Fremen, 2 = Harkonnen, 3 = Imperial/CHOAM
    int factionOf[11];
    int indexOf[11];
    int count = 0;

    std::cout << "People here:" << std::endl;
    for (int i = 0; i < 3; i++) {
        if (atreidesChars[i].getLocation() == current) {
            factionOf[count] = 0;
            indexOf[count] = i;
            std::cout << count + 1 << ". " << atreidesChars[i].getName() << " (House Atreides)" << std::endl;
            count++;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (fremenChars[i].getLocation() == current) {
            factionOf[count] = 1;
            indexOf[count] = i;
            std::cout << count + 1 << ". " << fremenChars[i].getName() << " (Fremen)" << std::endl;
            count++;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (harkChars[i].getLocation() == current) {
            factionOf[count] = 2;
            indexOf[count] = i;
            std::cout << count + 1 << ". " << harkChars[i].getName() << " (House Harkonnen)" << std::endl;
            count++;
        }
    }
    for (int i = 0; i < 2; i++) {
        if (imperialChars[i].getLocation() == current) {
            factionOf[count] = 3;
            indexOf[count] = i;
            std::cout << count + 1 << ". " << imperialChars[i].getName() << " (Imperium/CHOAM)" << std::endl;
            count++;
        }
    }

    if (count == 0) {
        std::cout << "There is no one to talk to here but the wind." << std::endl;
        return;
    }
    std::cout << count + 1 << ". Walk away" << std::endl;
    int choice = readMenuChoice(1, count + 1);
    if (choice == count + 1) {
        return;
    }

    int faction = factionOf[choice - 1];
    int index = indexOf[choice - 1];
    if (faction == 0) {
        talkToAtreides(index);
    } else if (faction == 1) {
        talkToFremen(index);
    } else if (faction == 2) {
        talkToHarkonnen(index);
    } else {
        talkToImperial(index);
    }
}

void Game::talkToAtreides(int index) {
    player.useAction();
    atreidesChars[index].displayDialogue();
    atreidesChars[index].giveHint();
    atreidesChars[index].increaseFriendship(10);
    if (!atreidesChars[index].hasUnlocked()) {
        int li = findLocationIndex(atreidesChars[index].getLocationToUnlock());
        if (li != -1 && !locations[li].isUnlocked()) {
            locations[li].unlock();
        }
        atreidesChars[index].unlockLocation();
    }
}

void Game::talkToFremen(int index) {
    fremenChars[index].updateWillingness(player.getBetrayal());
    fremenChars[index].displayDialogue();
    if (!fremenChars[index].isWillingToHelp()) {
        std::cout << fremenChars[index].getName()
                  << " turns away. Word of your betrayals has spread through the sietches." << std::endl;
        return;
    }
    std::cout << "1. Chat (raises friendship)" << std::endl;
    std::cout << "2. Ask for stillsuit repair" << std::endl;
    std::cout << "3. Ask for help with the shelter" << std::endl;
    std::cout << "4. Ask them to source spice" << std::endl;
    std::cout << "5. Leave" << std::endl;
    int choice = readMenuChoice(1, 5);

    if (choice == 1) {
        player.useAction();
        int newFriendship = fremenChars[index].increaseFriendship(10);
        std::cout << "You share stories of distant worlds. Friendship with "
                  << fremenChars[index].getName() << " is now " << newFriendship << "." << std::endl;
    } else if (choice == 2) {
        int amount = fremenChars[index].repairStillsuit(player.getBetrayal());
        if (amount <= 0) {
            std::cout << fremenChars[index].getName() << " cannot help you now." << std::endl;
            return;
        }
        player.useAction();
        player.repairStillsuit(amount);
        std::cout << fremenChars[index].getName() << " patches and seals your stillsuit (+"
                  << amount << "). Integrity: " << player.getStillsuitIntegrity() << "/100." << std::endl;
    } else if (choice == 3) {
        if (fremenChars[index].isQuestCompleted()) {
            std::cout << fremenChars[index].getName()
                      << ": \"You have already honored the sietch, Doctor.\"" << std::endl;
            return;
        }
        if (player.hasItem(fremenChars[index].getQuestReward())) {
            std::cout << "You already carry a " << fremenChars[index].getQuestReward() << "." << std::endl;
            return;
        }
        if (!bundle.isItemNeeded(fremenChars[index].getQuestReward())) {
            std::cout << "The shelter already has a " << fremenChars[index].getQuestReward() << "." << std::endl;
            return;
        }
        if (fremenChars[index].getFriendship() < 30) {
            std::cout << fremenChars[index].getName()
                      << ": \"The sietch does not yet know you, outworlder. Earn our trust first.\"" << std::endl;
            return;
        }
        fremenChars[index].offerQuest();
        std::cout << "Accept?" << std::endl;
        if (!askYesNo()) {
            return;
        }
        if (!player.spendSpice(fremenChars[index].getQuestSpiceCost())) {
            std::cout << "You do not have enough spice. (You have "
                      << player.getSpice() << ".)" << std::endl;
            return;
        }
        if (player.getInventorySize() >= MAX_INVENTORY) {
            std::cout << "Your pack is full!" << std::endl;
            player.earnSpice(fremenChars[index].getQuestSpiceCost()); // give it back
            return;
        }
        player.useAction();
        fremenChars[index].completeQuest();
        fremenChars[index].increaseFriendship(20);
        player.addItem(makeItem(fremenChars[index].getQuestReward()));
        std::cout << fremenChars[index].getName() << ": \"Your water is ours, and ours is yours.\"" << std::endl;
        std::cout << "You receive: " << fremenChars[index].getQuestReward() << "." << std::endl;
    } else if (choice == 4) {
        int gift = fremenChars[index].sourceSpice();
        if (gift <= 0) {
            std::cout << fremenChars[index].getName()
                      << ": \"I have given what I can, Doctor.\"" << std::endl;
            return;
        }
        player.useAction();
        player.earnSpice(gift);
        std::cout << fremenChars[index].getName() << " quietly passes you " << gift
                  << " spice. (Total: " << player.getSpice() << ")" << std::endl;
    }
}

void Game::talkToHarkonnen(int index) {
    harkChars[index].displayDialogue();
    if (harkChars[index].hasDealtWith()) {
        std::cout << harkChars[index].getName()
                  << ": \"We have already done business, Doctor. Do not press your luck.\"" << std::endl;
        return;
    }
    if (player.hasItem(harkChars[index].getShortcutItem()) ||
        !bundle.isItemNeeded(harkChars[index].getShortcutItem())) {
        std::cout << harkChars[index].getName()
                  << ": \"It seems you have no need of my " << harkChars[index].getShortcutItem()
                  << ". A pity.\"" << std::endl;
        return;
    }
    harkChars[index].offerShortcut();
    std::cout << "(This deal will raise your Betrayal by "
              << harkChars[index].getBetrayalIncrease() << ".)" << std::endl;
    std::cout << "Accept the shortcut?" << std::endl;
    if (!askYesNo()) {
        return;
    }
    if (!player.spendSpice(harkChars[index].getShortcutCost())) {
        std::cout << "You cannot afford it. (You have " << player.getSpice() << " spice.)" << std::endl;
        return;
    }
    if (player.getInventorySize() >= MAX_INVENTORY) {
        std::cout << "Your pack is full!" << std::endl;
        player.earnSpice(harkChars[index].getShortcutCost());
        return;
    }
    player.useAction();
    harkChars[index].acceptShortcut();
    player.increaseBetrayal(harkChars[index].getBetrayalIncrease());
    player.addItem(makeItem(harkChars[index].getShortcutItem()));
    std::cout << "You receive: " << harkChars[index].getShortcutItem()
              << ". (Betrayal is now " << player.getBetrayal() << "/" << MAX_BETRAYAL << ".)" << std::endl;
}

void Game::talkToImperial(int index) {
    imperialChars[index].displayDialogue();
    if (imperialChars[index].hasBetrayed()) {
        std::cout << imperialChars[index].getName()
                  << ": \"Our arrangement is concluded, Doctor.\"" << std::endl;
        imperialChars[index].displayStatus();
        return;
    }
    if (player.hasItem(imperialChars[index].getShortcutItem()) ||
        !bundle.isItemNeeded(imperialChars[index].getShortcutItem())) {
        std::cout << imperialChars[index].getName()
                  << ": \"It seems you already possess a " << imperialChars[index].getShortcutItem()
                  << ". A pity.\"" << std::endl;
        return;
    }
    imperialChars[index].offerDeal();
    std::cout << "(This deal will raise your Betrayal by "
              << imperialChars[index].getBetrayalIncrease() << ".)" << std::endl;
    std::cout << "Accept the deal?" << std::endl;
    if (!askYesNo()) {
        return;
    }
    if (!player.spendSpice(imperialChars[index].getShortcutCost())) {
        std::cout << "You cannot afford it. (You have " << player.getSpice() << " spice.)" << std::endl;
        return;
    }
    if (player.getInventorySize() >= MAX_INVENTORY) {
        std::cout << "Your pack is full!" << std::endl;
        player.earnSpice(imperialChars[index].getShortcutCost());
        return;
    }
    player.useAction();
    imperialChars[index].acceptDeal();
    player.increaseBetrayal(imperialChars[index].getBetrayalIncrease());
    player.addItem(makeItem(imperialChars[index].getShortcutItem()));
    imperialChars[index].displayStatus();
    std::cout << "You receive: " << imperialChars[index].getShortcutItem()
              << ". (Betrayal is now " << player.getBetrayal() << "/" << MAX_BETRAYAL << ".)" << std::endl;
}

void Game::useItem() {
    // list consumable items (non-component items that restore the stillsuit)
    int usable[MAX_INVENTORY];
    int count = 0;
    for (int i = 0; i < player.getInventorySize(); i++) {
        Item item = player.getItem(i);
        if (!item.isBundleItem() && item.calculateStillSuitIntegrity() > 0) {
            usable[count] = i;
            std::cout << count + 1 << ". ";
            item.displayInfo();
            count++;
        }
    }
    if (count == 0) {
        std::cout << "You carry nothing you can use." << std::endl;
        return;
    }
    std::cout << count + 1 << ". Cancel" << std::endl;
    int choice = readMenuChoice(1, count + 1);
    if (choice == count + 1) {
        return;
    }
    Item chosen = player.getItem(usable[choice - 1]);
    int restore = (int)chosen.calculateStillSuitIntegrity();
    player.repairStillsuit(restore);
    player.removeItem(chosen.getName());
    std::cout << "You use the " << chosen.getName() << " (+" << restore
              << " stillsuit). Integrity: " << player.getStillsuitIntegrity() << "/100." << std::endl;
}

void Game::donateComponents() {
    if (player.getCurrentLocation() != "Sietch Tabr") {
        std::cout << "The Fremen shelter is being built at Sietch Tabr. Bring your components there." << std::endl;
        return;
    }
    bool donatedAny = false;
    bool foundOne = true;
    while (foundOne) {
        foundOne = false;
        for (int i = 0; i < player.getInventorySize(); i++) {
            Item item = player.getItem(i);
            if (item.isBundleItem() && bundle.isItemNeeded(item.getName())) {
                bundle.donateItem(item);
                player.removeItem(item.getName());
                donatedAny = true;
                foundOne = true;
                break;
            }
        }
    }
    if (!donatedAny) {
        std::cout << "You carry nothing the shelter still needs." << std::endl;
    } else {
        bundle.displayProgress();
    }
}

void Game::endDay() {
    player.advanceDay(ACTIONS_PER_DAY);
    player.degradeStillsuit(NIGHT_WEAR);
    std::cout << "Night falls over Arrakis. The desert cools and the stars burn clear." << std::endl;
    if (player.getCurrentDay() <= MAX_DAYS) {
        std::cout << "Day " << player.getCurrentDay() << " begins. Stillsuit: "
                  << player.getStillsuitIntegrity() << "/100. Shelter: "
                  << bundle.getDonatedCount() << "/" << BUNDLE_SIZE << " components." << std::endl;
    }
}

bool Game::checkWin() {
    return bundle.isComplete();
}

bool Game::checkLoss() {
    if (player.getStillsuitIntegrity() <= 0) {
        lossReason = "stillsuit";
        return true;
    }
    if (player.getBetrayal() >= MAX_BETRAYAL) {
        lossReason = "betrayal";
        return true;
    }
    if (player.getCurrentDay() > MAX_DAYS) {
        lossReason = "time";
        return true;
    }
    return false;
}

void Game::displayEnding() {
    int questsCompleted = 0;
    for (int i = 0; i < 3; i++) {
        if (fremenChars[i].isQuestCompleted()) {
            questsCompleted++;
        }
    }

    std::cout << std::endl;
    std::cout << "==============================================" << std::endl;
    if (playerWon) {
        std::cout << "                 VICTORY!                     " << std::endl;
        std::cout << "==============================================" << std::endl;
        std::cout << "The shelter hums to life at Sietch Tabr, and the" << std::endl;
        std::cout << "Fremen step out of the storm into safety." << std::endl;
        std::cout << "Dr. Strain completed the mission in " << player.getCurrentDay()
                  << " day(s)," << std::endl;
        std::cout << "completing " << questsCompleted << " of 3 Fremen quests." << std::endl;
        if (player.getBetrayal() == 0) {
            std::cout << std::endl;
            std::cout << "You never once dealt with the Harkonnens or the" << std::endl;
            std::cout << "Imperium. The Fremen chant your name in the deep" << std::endl;
            std::cout << "sietches: Lisan al-Strain, friend of the desert." << std::endl;
        } else if (player.getBetrayal() < 50) {
            std::cout << std::endl;
            std::cout << "But your Betrayal stands at " << player.getBetrayal()
                      << ". The Fremen accept" << std::endl;
            std::cout << "the shelter with wary eyes. Some debts come due later..." << std::endl;
        } else {
            std::cout << std::endl;
            std::cout << "Yet at Betrayal " << player.getBetrayal()
                      << ", the shelter stands on a foundation" << std::endl;
            std::cout << "of dirty deals. The Fremen take it - but they will" << std::endl;
            std::cout << "never call you friend. A hollow victory." << std::endl;
        }
    } else if (lossReason == "stillsuit") {
        std::cout << "                 GAME OVER                    " << std::endl;
        std::cout << "==============================================" << std::endl;
        std::cout << "Your stillsuit fails beneath the merciless sun." << std::endl;
        std::cout << "The desert takes what is owed. Your water returns" << std::endl;
        std::cout << "to the tribe." << std::endl;
    } else if (lossReason == "betrayal") {
        std::cout << "                 GAME OVER                    " << std::endl;
        std::cout << "==============================================" << std::endl;
        std::cout << "Word of your dealings spreads through the sietches." << std::endl;
        std::cout << "The Fremen cast you out, and no one crosses the" << std::endl;
        std::cout << "desert alone. Betrayal was your undoing." << std::endl;
    } else if (lossReason == "time") {
        std::cout << "                 GAME OVER                    " << std::endl;
        std::cout << "==============================================" << std::endl;
        std::cout << "The deadline passes with the dawn of day " << MAX_DAYS + 1 << "." << std::endl;
        std::cout << "The unfinished shelter stands dark against the storm." << std::endl;
        std::cout << "You donated " << bundle.getDonatedCount() << " of "
                  << BUNDLE_SIZE << " components." << std::endl;
    } else {
        std::cout << "              MISSION ABANDONED               " << std::endl;
        std::cout << "==============================================" << std::endl;
        std::cout << "You board the next Guild heighliner off-world." << std::endl;
        std::cout << "The Fremen remain, as they always have, alone." << std::endl;
    }
    std::cout << "==============================================" << std::endl;
    std::cout << "Thanks for playing DUNE: SHELTER FOR THE FREMEN." << std::endl;
}
