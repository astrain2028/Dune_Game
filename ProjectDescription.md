# Project Description: Dune — Shelter for the Fremen

## Theme

You play as Dr. Austin Strain, a scientist stranded on the desert planet Arrakis. The Fremen,
the native people of Arrakis, are struggling to survive in the harsh desert environment. Your
goal is to collect five critical habitat components and donate them to power up a shelter for
the Fremen before your ten day mission deadline runs out.

The five components are Spice Melange, a Water Cache, Atomics, a Shield Generator Component,
and a Crysknife. Each item must be found, earned, or purchased through exploration and
character interactions across six locations: the Research Outpost, Arrakeen, Sietch Tabr, the
Harkonnen Outpost, the Emperor's Palace, and the Sandworm Fields. Eleven characters from the
Dune universe, spanning four factions, either help you or tempt you into dangerous deals.

## Planned Classes

- **Item** — a single collectible object: name, type, spice value, whether it is a habitat
  (bundle) component, and how much stillsuit integrity it restores when used.
- **Character** — base class every character type inherits from: name, location, friendship
  level, quest description, quest completion state, and quest reward.
- **FremenCharacter** (inherits Character) — Chani, Stilgar, Shai-Hulud. Repair the stillsuit
  based on Betrayal level, offer bundle items through quests, and source spice.
- **AtreidesCharacter** (inherits Character) — Paul, Jessica, Gurney. Give hints and unlock
  locations without raising Betrayal.
- **HarkonnenCharacter** (inherits Character) — Feyd-Rautha, Rabban, the Baron. Offer shortcut
  items that raise the Betrayal counter.
- **ImperialCHOAMCharacter** (inherits Character) — the Emperor and the CHOAM Representative.
  The most powerful shortcuts, at the highest Betrayal cost of any faction.
- **Player** — Dr. Strain: current day, stillsuit integrity, spice, current location, an
  inventory of Item objects, Betrayal counter, and actions remaining.
- **Bundle** — tracks the five required habitat components in an Item array with a parallel
  boolean array of what has been donated.
- **Location** — a visitable place: description, locked/unlocked state, and an array of
  connected location names that feeds the BFS pathfinder.
- **Game** — the master class: runs the game loop, menus, dashboard, map, character
  interactions, win/loss checks, and endings.

## Limited Resources

- **Spice** is the currency. You start with 20 and earn more by searching locations (the
  Sandworm Fields are richest) or asking Fremen allies to source it. Fremen quests and all
  faction shortcuts cost spice, and there is not enough to buy everything — you must choose.
- **Stillsuit integrity** is the survival resource (0–100). Traveling, searching, and ending
  the day all wear it down. If it reaches 0, the desert kills you. It can only be restored by
  Fremen repairs (which degrade as your Betrayal rises) or a consumable water item.
- **Actions** are the daily budget: 4 per day, spent on travel, searching, and talking.

## Handling Time

Time is measured in days with a hard deadline of Day 10. Each day grants 4 actions; when they
are spent (or whenever the player chooses) the day ends, which advances the calendar, refreshes
actions, and wears the stillsuit by 5. Losing happens the moment the calendar passes Day 10
with the shelter incomplete.

## Extra Credit

- **BFS pathfinding (implemented):** the six locations form a graph, with each Location storing
  its connections. Travel runs a breadth-first search across unlocked locations only, prints
  the shortest route (e.g. `Research Outpost -> Arrakeen -> Harkonnen Outpost`), and charges
  stillsuit wear per leg of the route, so distance has a real cost.
- **Multiple endings (implemented):** the victory text changes based on the final Betrayal
  level (0 = "Lisan al-Strain", under 50 = wary acceptance, 50+ = hollow victory) and reports
  how many Fremen quests were completed. There are four distinct loss endings (stillsuit
  failure, Betrayal 100, deadline passed, mission abandoned).

## Tradeoff System

The Harkonnens and the Imperium are this game's JojaMart. Every habitat component has two
paths:

- **The honorable path** — earn Fremen trust through conversation, then complete their quests,
  or find components hidden in dangerous locations. Slower and more expensive in actions, but
  it costs no Betrayal and keeps the Fremen willing to repair your stillsuit.
- **The shortcut path** — buy the same components instantly from the Harkonnens (+20 Betrayal
  each) or from the Emperor and CHOAM (+30 each). Faster, but at Betrayal 50 every Fremen
  refuses to help you (no repairs, no quests, no spice), and at 100 you lose outright.

The tension: shortcuts save precious days, but they cut you off from the only sustainable
source of stillsuit repair — and taint your ending even if you win.

## Mapping Style

The map is a graph of six named locations rather than a grid. The in-game map screen lists
every location with its lock status, the connections leading out of it, and a marker for the
player's position:

```
============= MAP OF ARRAKIS =============
* - Research Outpost
      connects to: Arrakeen, Sandworm Fields
  - Arrakeen
      connects to: Research Outpost, Sietch Tabr, Harkonnen Outpost, Emperor's Palace
  ...
(* = your current location)
```

Arrakeen acts as the central hub; the Sandworm Fields are reachable only through the open
desert routes, and three locations start locked until an Atreides ally opens them.

## Win / Lose Conditions

- **Win:** donate all five habitat components at Sietch Tabr on or before Day 10.
- **Lose:** stillsuit integrity reaches 0, Betrayal reaches 100, the deadline passes with the
  shelter incomplete, or the player abandons the mission.
