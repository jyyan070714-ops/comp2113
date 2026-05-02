#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"
#include "card.h"

struct Enemy;

// Represents the player, including stats, hand cards, relics, and combat actions.
class Player {
public:
    // Basic health, block, and energy values.
    int hp;
    int maxHp;
    int block;
    int energy;
    int maxEnergy;

    // Attack bonuses used during turns and combat.
    int tempAttackBonus;
    int combatAttackBonus;

    vector<CardID> hand;   // only hand, no deck/discard

    // Relic flags that enable special player effects.
    bool relicWarriorBlade;
    bool relicMagicPotion;
    bool relicLifeAmulet;
    bool relicEnergyCrystal;

    // Turn and difficulty tracking.
    int attackPlayedThisTurn;
    int difficulty;

    // Create and initialize an empty player object.
    Player();

    // Initialize player stats based on difficulty.
    void init(int diff);

    // Handle turn start and turn end behavior.
    void startTurn();
    void endTurn();

    // Card and combat actions.
    void drawCards(int num);   // draw from globalCardPool
    void takeDamage(int dmg);
    void addBlock(int amount);
    void heal(int amount);
    void dealDamageTo(Enemy& enemy, int baseDamage);

    void addCardToHand(CardID cardId);   // for events that give immediate card

    // Apply a relic effect to the player.
    void applyRelic(RelicID relic);

    // Handle combat start and combat end behavior.
    void startCombat();
    void endCombat();

    // Print current player information.
    void printStatus() const;
    void printHand() const;
};

#endif // PLAYER_H
