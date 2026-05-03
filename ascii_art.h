#ifndef ASCII_ART_H
#define ASCII_ART_H

#include <string>
/**
 * @brief Prints an ASCII art representation of the player character to the console.
 * @param none
 * @return void
 */
void printPlayerArt();
/**
 * @brief Prints an ASCII art representation of an enemy based on its name.
 *        Different enemies (Small Slime, Goblin Marauder, Goblin Boss) have distinct art.
 * @param enemyName The name of the enemy, used to select the appropriate ASCII art.
 * @return void
 */
void printEnemyArt(const std::string& enemyName);

#endif
