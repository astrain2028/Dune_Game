# CSCI1300_Final
Final project for CSCI1300

# CSCI 1300 Final Project - Project Description

## Theme

Dune. The player is Dr. Austin Strain, a scientist stranded on the desert planet Arrakis. The Fremen, the native people of Arrakis, are struggling to survive in the harsh environment. Dr. Strain must power up a habitat that will make life survivable for the Fremen before the mission deadline runs out. Standing in the way are powerful corporate and political forces including the Harkonnens, CHOAM, and the Emperor, all of whom want to exploit Arrakis for its spice rather than let the Fremen thrive.

## Goal

Collect all 5 required habitat components and donate them to power the habitat before Day 10 ends. The ending the player receives depends on how many shortcuts they took from corporate factions, whether they completed Stilgar's quest to secure the Atomics, and whether their stillsuit held out long enough to survive the journey.

## How to Compile and Run

TBA

## How to Play

TBA

## Classes

### Item
Represents a single collectible object in the game world. Stores the item name, type, spice value, whether it is required for the habitat bundle, and how much stillsuit integrity it restores if used. Examples include Spice Melange, Water Cache, Atomics, Shield Generator Component, and Crysknife.

### Bundle
Tracks the 5 required habitat components. Stores an array of required Item objects and a parallel array of booleans tracking which have been donated. Provides functions to check whether a specific item is still needed, donate an item, check whether the bundle is complete, and display current progress.

### Character
Represents a named character Dr. Strain can interact with. Stores the character name, home location, a quest description, whether their quest has been completed, and a reward item. Characters can talk, give quests, give rewards, and affect the Betrayal counter or Fremen trust depending on who they are. Characters include Paul Atreides, Chani, Stilgar, Jessica, Gurney, Feyd-Rautha, Shai Hulud, and the Emperor.

### Player
Represents Dr. Austin Strain. Stores the player name, current day, stillsuit integrity, spice amount, current location, an inventory array of Item objects, and the Betrayal counter. Provides functions to move between locations, add and remove items, spend and earn spice, degrade and repair the stillsuit, and display current stats.

### Location
Represents a visitable place on Arrakis. Stores the location name, a short description, whether it is currently unlocked, and an array of connected location names used for map display and pathfinding. Provides functions to unlock the location and retrieve its connections for the BFS algorithm.

### Game
The top level class that owns and coordinates everything. Stores a Player, an array of Characters, an array of Locations, and a Bundle. Runs the main game loop, displays the dashboard and map, processes player menu choices, handles character interactions and donations, tracks win and loss conditions, and displays the final ending.

## Resources

### Stillsuit Integrity
Dr. Strain's stillsuit recycles body water to keep him alive. It starts at 10 each day and degrades with risky actions. Traveling through the Sandworm Fields costs 3 integrity, salvaging at the Harkonnen Outpost costs 2, and traveling between safe locations costs 1. Resting at the Research Outpost restores 5. Fremen characters repair it for free if Betrayal is 0 but charge spice if Betrayal is high. If stillsuit integrity hits 0 Dr. Strain dies of dehydration and the game ends immediately.

### Spice
Spice Melange is the currency of Arrakis and replaces gold. It is earned by harvesting in the Sandworm Fields or trading with certain characters. It is spent in Arrakeen, with CHOAM, or to bribe characters. Taking corporate shortcuts costs spice and raises Betrayal. Fremen characters may give spice as quest rewards.

### Betrayal
A counter that tracks how much Dr. Strain has cooperated with corporate and imperial factions. It goes up by 1 each time the player takes a shortcut from Feyd-Rautha, the Emperor, or CHOAM. It affects which ending the player receives and whether Fremen characters are willing to help freely or demand spice payment.

## Time Limit

The mission lasts 10 days. Each day the player has a set number of actions. When actions run out the day ends automatically. When Day 10 ends without all 5 habitat components donated, the game ends in a loss.

## Tradeoff System

Three corporate and imperial factions offer shortcuts to make the game easier in the short term at the cost of raising Betrayal.

Feyd-Rautha at the Harkonnen Outpost can sell rare bundle items or repair the stillsuit for spice, skipping the need to complete Fremen quests.

The Emperor at his Palace can grant access to locked locations or provide bundle items through political favors, raising Betrayal significantly.

CHOAM operates through merchants in Arrakeen and offers the widest range of shortcuts including bundle items, spice, and stillsuit repair, all at the cost of raising Betrayal.

Using these factions saves time and stillsuit integrity but pushes the player toward worse endings. The Fremen notice every deal made with their oppressors.

## Map

Arrakeen is the central hub that connects to all other locations. The map is displayed as an ASCII diagram in the dashboard on every turn. The player's current location is marked with an asterisk. Locked locations are shown with dashes around them until unlocked by completing the relevant character quest.

Planned layout:

Emperor's Palace
      |
Arrakeen -- Harkonnen Outpost
      |
Research Outpost -- Sandworm Fields
      |
Sietch Tabr

## Win and Loss Conditions

Best Ending - The Fremen Are Free
All 5 items donated, Betrayal at 0, and Stilgar's quest completed to secure the Atomics in Sietch Tabr. The habitat powers up, terraforming begins, spice production collapses, and CHOAM and the Emperor lose their grip on the universe.

Bittersweet Ending - A Fragile Peace
All 5 items donated and Betrayal at 1 or 2. The habitat is powered but the Fremen distrust Dr. Strain. Terraforming begins slowly while corporate interests maintain a foothold on Arrakis.

Bad Ending - CHOAM Wins
All 5 items donated but Betrayal at 3 or more. CHOAM seizes the habitat and uses it to expand spice production. The Fremen remain oppressed.

Mutual Destruction Ending - The Atomics Detonate
All 5 items donated and Betrayal at 0, but Stilgar's quest was not completed. CHOAM sees they are losing control of Arrakis and detonates the Atomics. Everyone loses.

Dehydration Ending - Lost in the Desert
Stillsuit integrity hits 0 at any point. Dr. Strain dies in the desert. The habitat is never powered.

Time Ending - The Mission Fails
Day 10 ends without all 5 items donated. The Fremen are left without a habitat and Arrakis remains under corporate control.

## Extra Credit

Option 1 - Shortest Path Algorithm

A breadth first search algorithm will be implemented in the Game class to help the player navigate between locations. Since each Location stores an array of connected location names, BFS can walk those connections to find the shortest route from Dr. Strain's current location to any destination. The path and estimated stillsuit cost will be displayed to the player when they choose to travel. An array based queue with head and tail indices will be used to implement BFS without relying on any data structures outside of what was taught in class.

Example output:

Recommended route to Sietch Tabr
Research Outpost to Arrakeen to Sietch Tabr
Estimated stillsuit cost: 2
