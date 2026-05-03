#include "ascii_art.h"
#include <iostream>

using namespace std;
/**
 * @brief Prints an ASCII art representation of the player character to the console.
 * @param none
 * @return void
 */
void printPlayerArt() {
    cout << R"(
   _______
  |   o   |
  |  /|\  |
  |  / \  |
  |_______|
)";
}
/**
 * @brief Prints an ASCII art representation of an enemy based on its name.
 *        Different enemies have different art styles.
 * @param enemyName The name of the enemy (e.g., "Small Slime", "Goblin Marauder", "Goblin Boss").
 * @return void
 */

void printEnemyArt(const string& enemyName) {
    if (enemyName == "Small Slime") {
        cout << R"(
   ______
  /      \
 /   o o  \
|    ^    |
|   vvv   |
 \______/
)";
    }
    //elite monster
    else if (enemyName == "Goblin Marauder") {
        cout << R"(
    +---+
    | o |
    | ^ |
    |vvv|
    |   |
    +---+
)";
    }
    //final BOSS
    else if (enemyName == "Goblin Boss") {
        cout << R"(
    +----+
   /      \
  |  o o  |
  |   ^   |
  |  /|\  |
  | /   \ |
  +-------+
)";
    }
    else {
        cout << R"(
   +---+
   | o |
   | ^ |
   +---+
)";
    }
}
