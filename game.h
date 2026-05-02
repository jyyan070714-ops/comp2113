#ifndef GAME_H
#define GAME_H

#include "common.h"

// What it does: starts the game flow by showing the main menu and handling menu choices.
// Inputs: none.
// Outputs: none directly; runs the game loop and prints menu/game status to the console.
void runGame();

// What it does: displays the main menu and lets the player choose between starting,
// continuing, or exiting the game.
// Inputs: none.
// Outputs: none directly; reads user input and triggers the selected menu action.
void mainMenu();

// What it does: begins a new playthrough, asks for difficulty, builds a fresh player,
// and progresses through the route from the start.
// Inputs: none.
// Outputs: none directly; updates game state, prints progress, and may write save data.
void newGame();

// What it does: loads a saved game and resumes play from the last saved node.
// Inputs: none.
// Outputs: none directly; restores game state from disk, prints progress, and may write save data.
void continueGame();

#endif // GAME_H
