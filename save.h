#ifndef SAVE_H
#define SAVE_H

#include "common.h"

class Player;

// Save the current player state and map progress.
void saveGame(const Player& player, int currentNodeIndex, bool gameComplete);

// Load player state and map progress from the save file.
bool loadGame(Player& player, int& currentNodeIndex, bool& gameComplete);

// Check whether a save file exists.
bool saveFileExists();

#endif // SAVE_H
