#include "common.h"
#include "card.h"

// The global card pool tracks which CardIDs are currently available for player for post-combat rewards
// Power cards (12-13) and Rare cards (14-18) are excluded from the initial pool
vector<CardID> globalCardPool;

//
void initGlobalCardPool() {
    globalCardPool.clear();

    // Basic cards (0-5)
    // They are always available from the start
    globalCardPool.push_back(STRIKE);
    globalCardPool.push_back(DEFEND);
    globalCardPool.push_back(HEAVY_STRIKE);
    globalCardPool.push_back(IRON_WALL);
    globalCardPool.push_back(FOCUS);
    globalCardPool.push_back(EMERGENCY_HEAL);

    // Advanced cards (6-11)
    // Available from the start but more situational
    globalCardPool.push_back(ANGRY_STRIKE);
    globalCardPool.push_back(TACTICIAN);
    globalCardPool.push_back(DOUBLE_STRIKE);
    globalCardPool.push_back(FLAME_SHIELD);
    globalCardPool.push_back(LIFE_DRAIN);
    globalCardPool.push_back(PREPARATION);

    // Power cards (12-13) and Rare cards (14-18) are not included initially
    // They are unlocked and added to the pool through addCardToGlobalPool()
}

// Adds a single card to the global pool, making it eligible for future rewards
// Prints a confirmation message
void addCardToGlobalPool(CardID id) {
    globalCardPool.push_back(id);
    Card c = getCardById(id);
    cout << "Card \"" << c.name << "\" has been added to the global pool.\n";
}
