#include "ascii_art.h"
#include <iostream>

using namespace std;
//player
void printPlayerArt() {
    cout << R"(
   _______
  |   o   |
  |  /|\  |
  |  / \  |
  |_______|
)";
}
//small slime
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
