#include "save.h"
#include "player.h"
#include <fstream>
#include <iostream>

using namespace std;

// Fixed save file name used by the game.
static const string SAVE_FILE = "savegame.txt";

// Save the current player and map progress to a text file.
void saveGame(const Player& player, int currentNodeIndex, bool gameComplete) {
    ofstream ofs(SAVE_FILE);
    if (!ofs) {
        cout << "Save failed: cannot create file.\n";
        return;
    }

    // Save basic player and game progress data.
    ofs << "difficulty " << player.difficulty << "\n";
    ofs << "hp " << player.hp << "\n";
    ofs << "maxHp " << player.maxHp << "\n";
    ofs << "maxEnergy " << player.maxEnergy << "\n";
    ofs << "currentNode " << currentNodeIndex << "\n";
    ofs << "gameComplete " << (gameComplete ? 1 : 0) << "\n";

    // Save relic ownership as 0 or 1 values.
    ofs << "relicWarriorBlade " << (player.relicWarriorBlade ? 1 : 0) << "\n";
    ofs << "relicMagicPotion " << (player.relicMagicPotion ? 1 : 0) << "\n";
    ofs << "relicLifeAmulet " << (player.relicLifeAmulet ? 1 : 0) << "\n";
    ofs << "relicEnergyCrystal " << (player.relicEnergyCrystal ? 1 : 0) << "\n";

    // Note: global card pool is not saved; new game resets to basic+advanced.
    cout << "Game saved.\n";
}

// Load player and map progress from the save file.
bool loadGame(Player& player, int& currentNodeIndex, bool& gameComplete) {
    ifstream ifs(SAVE_FILE);
    if (!ifs) {
        cout << "No save file found.\n";
        return false;
    }

    string key;
    int val;

    // Read and validate basic player and game progress data.
    if (!(ifs >> key >> player.difficulty) || key != "difficulty") {
        cout << "Save file is corrupted.\n";
        return false;
    }
    if (!(ifs >> key >> player.hp) || key != "hp") {
        cout << "Save file is corrupted.\n";
        return false;
    }
    if (!(ifs >> key >> player.maxHp) || key != "maxHp") {
        cout << "Save file is corrupted.\n";
        return false;
    }
    if (!(ifs >> key >> player.maxEnergy) || key != "maxEnergy") {
        cout << "Save file is corrupted.\n";
        return false;
    }
    if (!(ifs >> key >> currentNodeIndex) || key != "currentNode") {
        cout << "Save file is corrupted.\n";
        return false;
    }
    if (!(ifs >> key >> val) || key != "gameComplete" || (val != 0 && val != 1)) {
        cout << "Save file is corrupted.\n";
        return false;
    }
    gameComplete = (val == 1);

    // Read and validate relic ownership values.
    if (!(ifs >> key >> val) || key != "relicWarriorBlade" || (val != 0 && val != 1)) {
        cout << "Save file is corrupted.\n";
        return false;
    }
    player.relicWarriorBlade = (val == 1);
    if (!(ifs >> key >> val) || key != "relicMagicPotion" || (val != 0 && val != 1)) {
        cout << "Save file is corrupted.\n";
        return false;
    }
    player.relicMagicPotion = (val == 1);
    if (!(ifs >> key >> val) || key != "relicLifeAmulet" || (val != 0 && val != 1)) {
        cout << "Save file is corrupted.\n";
        return false;
    }
    player.relicLifeAmulet = (val == 1);
    if (!(ifs >> key >> val) || key != "relicEnergyCrystal" || (val != 0 && val != 1)) {
        cout << "Save file is corrupted.\n";
        return false;
    }
    player.relicEnergyCrystal = (val == 1);

    // Check loaded values for impossible states.
    if (player.maxHp <= 0 || player.hp < 0 || player.hp > player.maxHp || player.maxEnergy <= 0 || currentNodeIndex < 0) {
        cout << "Save file is corrupted.\n";
        return false;
    }

    // Reset player hand and other combat state
    player.hand.clear();
    player.block = 0;
    player.energy = player.maxEnergy;
    player.tempAttackBonus = 0;
    player.combatAttackBonus = 0;
    player.attackPlayedThisTurn = 0;

    // Global pool will be reinitialized by the caller (newGame/continueGame)
    cout << "Game loaded successfully.\n";
    return true;
}

// Check whether a save file currently exists.
bool saveFileExists() {
    ifstream f(SAVE_FILE);
    return f.good();
}
