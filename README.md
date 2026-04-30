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

---

4. File Input/Output

   This project satisfies the file input/output requirement through the save and load system.

   - The main file I/O code is implemented in `save.cpp` and declared in `save.h`.
   - The game uses C++ file streams from `<fstream>` to save and load player progress through an external text file named `savegame.txt`.
   - When the player finishes a map node, `game.cpp` calls `saveGame(player, currentNode + 1, gameComplete)`.
   - Inside `saveGame()`, an `ofstream` is used to write the player's current game state into `savegame.txt`.
   - The saved data includes the player's difficulty, HP, max HP, max energy, current map node, whether the game is completed, and the relics the player has obtained.
   - When the player chooses **Continue Game** from the main menu, `game.cpp` calls `loadGame()`.
   - Inside `loadGame()`, an `ifstream` is used to read data from `savegame.txt` and restore the player's previous progress.
   - The function also validates the file contents, such as checking that HP values are valid and relic values are either `0` or `1`.
   - If the save file does not exist or contains invalid data, the game displays an error message and does not load the corrupted save.
   - The project also uses `saveFileExists()` in `save.cpp`, which opens `savegame.txt` with an `ifstream` to check whether a save file is available.

---

5. Program Codes in Multiple Files

   This project satisfies the "program codes in multiple files" requirement because the program is divided into multiple `.cpp` and `.h` files instead of being written in a single file.

   - `main.cpp` is used as the entry point of the program.
   - `main.cpp` calls `runGame()` to start the game.
   - The main game loop, menu system, new game logic, and continue game logic are implemented in `game.cpp` and declared in `game.h`.
   - Different features of the game are separated into their own source and header files.
   - `player.cpp` and `player.h` handle the player's data and actions, such as HP, energy, blocking, healing, and relic effects.
   - `card.cpp` and `card.h` define the card system, including card information and card effects.
   - `enemy.cpp` and `enemy.h` manage enemy data and enemy behavior.
   - `combat.cpp` and `combat.h` control the battle system between the player and enemies.
   - `map.cpp` and `map.h` handle the game route.
   - `event.cpp` and `event.h` handle random events.
   - `relic.cpp` and `relic.h` handle relic rewards.
   - `save.cpp` and `save.h` handle saving and loading game progress.
   
   - This structure makes the project easier to read, maintain, and debug because each file has a clear responsibility.

---

6. Multiple Difficulty Levels

   This project satisfies the "Multiple Difficulty Levels" requirement because the game allows the player to choose between three difficulty levels when starting a new game: Easy, Normal, and Hard.

   - In `game.cpp`, the `newGame()` function displays a difficulty selection menu with three options: Easy, Normal, and Hard.
   
   - The player's choice is converted into a difficulty value and passed into `player.init(difficulty)`. This means the selected difficulty becomes part of the player's game state.
   - The difficulty settings are defined in `common.h` using constant double arrays.
   - `const double DIFFICULTY_HP_SCALE[] = {1.2, 1.0, 0.8};` controls the player's HP scaling.
   - `const double DIFFICULTY_ENEMY_HP_SCALE[] = {0.8, 1.0, 1.4};` controls enemy HP scaling.
   - `const double DIFFICULTY_ENEMY_DMG_SCALE[] = {0.8, 1.0, 1.3};` controls enemy damage scaling.
   - These values make the game easier or harder depending on the selected mode.
   
   - In `player.cpp`, the player's maximum HP is scaled based on difficulty.
   - Easy gives the player more HP, Normal keeps the default HP, and Hard gives the player less HP.
   - 
   - In `enemy.cpp`, enemy HP and enemy damage are also scaled based on difficulty.
   - Easy makes enemies weaker, Normal keeps enemies at standard strength, and Hard makes enemies stronger by increasing their HP and damage.
   
   - The selected difficulty is also saved in `save.cpp` as part of the save file using `ofs << "difficulty " << player.difficulty << "\n";`.
   - When loading a saved game, the difficulty value is read back and used again.
   - This allows the game to continue with the same difficulty level the player originally selected.





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
