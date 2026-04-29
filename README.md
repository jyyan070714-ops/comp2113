# comp2113

## Team Members

- Yan Jiayao (Github: jyyan070714-ops)
- Wan Ziran (Github: zoey555101)
- Sun Xiaosong (Github: Sun-xiaosong)
- Zhang Hongyi (Github: Jamesss666)
- Yan Zihan (Github: yanzihan0320)

## Game Description

Slay the Spire - Text-Based Game is a terminal-based turn-based card adventure game inspired by Slay the Spire. The player takes on the role of a hero who fights enemies along a fixed path with multiple node types (fight, event, rest, boss), using attack and skill cards to deal damage or gain block, while carefully managing energy and hand size. The game includes the following core features:

- Card Combat: Each turn the player draws cards, spends energy to play them, and then ends the turn, after which the enemy attacks.
- Relic System: After defeating enemies, the player may randomly obtain relics. Each relic provides a unique passive effect (e.g., first attack each turn deals +2 damage, draw 2 extra cards at combat start, heal 3 HP after combat, +1 max energy, etc.).
- Difficulty Levels: The player can choose from multiple difficulty levels at the start of the game, affecting starting HP, max energy, and other parameters.
- Save / Load: The game supports saving the current progress (HP, relics, current node, difficulty, etc.) and loading it later to continue the adventure.

The entire game runs in a command-line interface, with numerical menus for interaction. It offers simple but rich gameplay that tests the player's strategy and resource management skills.

## Implemented Features

1. Random Event Generation
   The game includes a random event system that increases replayability and player choice.
   Detailed feature scope
   · Multiple unique event types are implemented:
   · Ancient Shrine
   · Hidden Trap
   · Wandering Merchant
   · Campfire Gathering
   · Cursed Well
   · Elite Ghost
   · Each event provides different outcomes (HP gain/loss, card rewards, card upgrades, risk-reward decisions).
   · Event outcomes directly affect progression through combat strength and survivability.
   How the coding elements support this feature
   · Random generation logic: triggerRandomEvent(Player&) selects one event via rand() % 6 (event.cpp).
   · Random reward selection: events and rewards use random indices from card pools (rareCards, filtered normal cards).
   · Random initialization: initRandom() seeds RNG using current time (common.h), called at menu startup (game.cpp).
   · Data-driven event effects: event actions manipulate Player state and globalCardPool, making events integrated with core gameplay loops.

---

2. Data Structures for Storing Data
   The game uses structured in-memory models to represent cards, map nodes, player state, and content pools.
   Detailed feature scope
   · Card metadata (cost, type, value, description, upgrade path) is centrally stored.
   · Route progression is represented as typed map nodes.
   · Player combat state and persistent meta-state (relics, HP, energy) are tracked.
   · Save/load stores key fields for session continuation.
   How the coding elements support this feature
   · enum-based identifiers (CardID, EnemyID, RelicID, NodeType in common.h) provide stable typed IDs.
   · Struct/class models:
   · Card struct (card.h)
   · Node struct (map.h)
   · Player class (player.h/.cpp)
   · Enemy struct/class (enemy.h/.cpp)
   · std::vector containers are used for flexible collections:
   · allCards, rareCards
   · globalCardPool
   · player hand
   · map route
   · Lookup and transformation helpers:
   · getCardById, getUpgradedVersion, isRareCard (card.cpp)
   · nodeTypeToString (map.cpp)
   · File persistence format (save.cpp) stores and restores structured game state as key-value records.

---

3. Dynamic Memory Management
   The combat flow uses runtime object allocation for enemies to support node-by-node enemy creation.
   Detailed feature scope
   · Enemies are created dynamically per node (Fight/Elite/Boss) based on route and difficulty.
   · Objects are destroyed immediately after each combat to prevent lifetime overlap and reduce retained memory.
   How the coding elements support this feature
   · Heap allocation: Enemy\* enemy = new Enemy(createEnemy(...)) in newGame() and continueGame() (game.cpp).
   · Explicit deallocation: delete enemy; is called after combat resolution.
   · Encapsulated creation logic: createEnemy(EnemyID, difficulty) builds scaled enemy instances (enemy.cpp), while dynamic allocation controls lifetime at runtime.
   · This design ensures enemy objects exist only when needed during each encounter.

## Compilation and Execution Instructions

Compilation Requirements
Compiler: g++ with C++11 or higher support
Operating System: Linux / macOS / Windows
Dependencies: No external libraries, only standard library used.

---

Compilation Commands
1.Navigate to the project directory by entering “cd /path/to/your/project”
2.Enter “make” to compile.
3.When compilation succeeds, enter “./game”. 
Then the game starts to run and you will see the following main menu options:

===== Slay the Spire Lite =====
1. New Game  //which means start a fresh playthrough
2. Continue Game  //which means load previously saved game
3. Exit  // which means exit the game
Choose:

Choose for your convenience!

---

Gameplay Logic
Navigate through nodes (combat, random events, rest sites) and ultimately defeat the final boss to win the game.

---

Auto-save
As you enter the save point(when the screen shows “Game saved.”), the game progress will automatically be saved. You can exit the game instantly, and continue by choosing Continue Game in main menu.
