# CSCI 1300 Final Project — Dune: Shelter for the Fremen

A text-based adventure game set on Arrakis, written in C++.
See [ProjectDescription.md](ProjectDescription.md) for the full design document.

## Theme

You play as Dr. Austin Strain, a scientist stranded on the desert planet Arrakis. The Fremen,
the native people of Arrakis, are struggling to survive in the harsh desert environment. Your
goal is to collect five critical habitat components and donate them to power up a shelter for
the Fremen before your ten day mission deadline runs out.

## Goal

The five components you must collect are Spice Melange, a Water Cache, Atomics, a Shield
Generator Component, and a Crysknife. Each item must be found, earned, or purchased through
exploration and character interactions across six locations including the Research Outpost,
Arrakeen, Sietch Tabr, the Harkonnen Outpost, the Emperor's Palace, and the Sandworm Fields.

You will interact with eleven characters from the Dune universe spanning four factions:

- **The Fremen** (Chani, Stilgar, and Shai-Hulud) will help you find items, source spice, and
  repair your stillsuit — if you have earned their trust.
- **The Atreides** (Paul, Jessica, and Gurney) will give you hints and unlock locations.
- **The Harkonnens** (Feyd-Rautha, Rabban, and the Baron) will offer dangerous shortcuts that
  raise your Betrayal counter.
- **The Emperor and CHOAM** will offer the most powerful shortcuts at the highest cost to the
  Fremen.

## How to compile and run

```
g++ -std=c++11 -Wall *.cpp -o main.exe
main.exe
```

Opening the project in VS Code and using the built-in build/debug task produces the same
`main.exe`, via `.vscode/tasks.json` and `.vscode/launch.json`.

## How to play

Every turn you pick an option from the main menu: view your dashboard or the map, travel,
search your current location, talk to someone, use an item, donate components at Sietch Tabr,
or end the day.

- Each day you have 4 actions. Traveling, searching, and talking each cost one.
- Travel uses BFS pathfinding over the map graph — the further the destination, the more your
  stillsuit wears down along the way.
- Searching harvests spice and can uncover hidden components. Fremen allies repair your
  stillsuit, source spice, and trade components for spice once you have earned their trust.
- Harkonnen and Imperial characters sell components instantly, but raise your Betrayal.
  At Betrayal 50+ the Fremen refuse to help you.

**Win:** donate all 5 habitat components at Sietch Tabr before the end of Day 10. Your ending
depends on your final Betrayal level and how many Fremen quests you completed.
**Lose:** your stillsuit integrity reaches 0, your Betrayal reaches 100, or the deadline passes.

## Classes

| File | Purpose |
|---|---|
| `Item.h/.cpp` | A collectible object: name, type, spice value, bundle flag, stillsuit restoration. |
| `Character.h/.cpp` | Base class for all characters: name, location, friendship, quest state. |
| `FremenCharacter.h/.cpp` | Fremen allies: stillsuit repair, spice sourcing, bundle-item quests. |
| `AtreidesCharacter.h/.cpp` | Atreides allies: hints and location unlocks, no Betrayal cost. |
| `HarkonnenCharacter.h/.cpp` | Harkonnen dealers: shortcut items that raise Betrayal. |
| `ImperialCHOAMCharacter.h/.cpp` | Emperor/CHOAM: the most powerful shortcuts, highest Betrayal cost. |
| `Player.h/.cpp` | Dr. Strain: day, stillsuit, spice, inventory, Betrayal, actions. |
| `Bundle.h/.cpp` | Tracks the five required components and which have been donated; loads the component list from `items.txt`. |
| `Location.h/.cpp` | A visitable place: description, lock state, and graph connections for BFS. |
| `Game.h/.cpp` | The master class: game loop, menus, interactions, win/loss, endings. |
| `main.cpp` | Creates a Game object and calls startGame. Nothing else. |

## File input

The five required habitat components (name, type, and spice value) are read at startup from
`items.txt`, a plain comma-separated text file in the project root, rather than being hardcoded
in `Bundle`'s constructor. If the file is missing, `Bundle` falls back to a hardcoded default
list so the game still runs.

## Extra credit

- **BFS pathfinding:** travel routes are computed with a breadth-first search over the
  location graph, restricted to unlocked locations, with stillsuit wear charged per leg.
- **Multiple endings:** three tiered victory endings based on final Betrayal (plus a Fremen
  quest tally) and four distinct loss endings.
