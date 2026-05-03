#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <limits>

using namespace std;

/**
 * @brief Initializes the random number generator with a seed based on current time.
 *        Call this once at the beginning of the program to ensure different random sequences.
 * @param none
 * @return void
 */
inline void initRandom() { srand(static_cast<unsigned int>(time(nullptr))); }
/**
 * @brief Generates a random integer within [min, max] (inclusive).
 * @param min Minimum possible value.
 * @param max Maximum possible value.
 * @return int A random integer between min and max.
 */
inline int randomRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Node Types (Map)
enum NodeType {
    FIGHT,
    EVENT,
    ELITE,
    REST,
    BOSS
};

//  Card Types 
enum CardType {
    ATTACK,
    SKILL
};

// Card ID Enum
enum CardID {
    // Basic cards 
    STRIKE,
    DEFEND,
    HEAVY_STRIKE,
    IRON_WALL,
    FOCUS,
    EMERGENCY_HEAL,

    // Advanced cards 
    ANGRY_STRIKE,
    TACTICIAN,
    DOUBLE_STRIKE,
    FLAME_SHIELD,
    LIFE_DRAIN,
    PREPARATION,

    // Power cards 
    POWER_POTION,
    LIFE_CONTRACT,

    // Rare cards 
    METEOR,
    HOLY_BARRIER,
    FURY_COMBO,
    SOUL_DRAIN,
    TIME_WARP,

    // Upgraded cards (start from 100 to avoid conflict)
    STRIKE_PLUS = 100,
    DEFEND_PLUS,
    HEAVY_STRIKE_PLUS,
    IRON_WALL_PLUS,
    FOCUS_PLUS,
    EMERGENCY_HEAL_PLUS,
    ANGRY_STRIKE_PLUS,
    TACTICIAN_PLUS,
    DOUBLE_STRIKE_PLUS,
    FLAME_SHIELD_PLUS,
    LIFE_DRAIN_PLUS,
    PREPARATION_PLUS,
    POWER_POTION_PLUS,
    LIFE_CONTRACT_PLUS,
    METEOR_PLUS,
    HOLY_BARRIER_PLUS,
    FURY_COMBO_PLUS,
    SOUL_DRAIN_PLUS,
    TIME_WARP_PLUS,

    TOTAL_CARD_IDS
};

// Enemy ID Enum
enum EnemyID {
    ENEMY_SLIME,
    ENEMY_GOBLIN,
    ENEMY_GOBLIN_BOSS
};

// Relic ID Enum 
enum RelicID {
    RELIC_WARRIOR_BLADE,
    RELIC_MAGIC_POTION,
    RELIC_LIFE_AMULET,
    RELIC_ENERGY_CRYSTAL,
    TOTAL_RELICS
};

// Forward Declarations
class Player;
struct Enemy;

//Game Constants 
const int STARTING_HP = 60;
const int STARTING_MAX_HP = 60;
const int STARTING_ENERGY = 3;
const int HAND_SIZE = 5;
const double DIFFICULTY_HP_SCALE[] = {1.2, 1.0, 0.8};
const double DIFFICULTY_ENEMY_HP_SCALE[] = {0.8, 1.0, 1.4};
const double DIFFICULTY_ENEMY_DMG_SCALE[] = {0.8, 1.0, 1.3};

// Global Card Pool (for drawing)
extern vector<CardID> globalCardPool;
/**
 * @brief Initializes the global card pool with the starting set of cards (basic + advanced).
 *        Call this at the beginning of a new game.
 * @param none
 * @return void
 */
void initGlobalCardPool();
/**
 * @brief Adds a card to the global card pool, making it available for future draws.
 * @param id The CardID of the card to add.
 * @return void
 */
void addCardToGlobalPool(CardID id);

#endif // COMMON_H
