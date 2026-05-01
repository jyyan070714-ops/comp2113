#include "player.h"
#include "enemy.h"
#include <algorithm>
#include <random>

using namespace std;

// Constructor: initialize all player stats, bonuses, relic flags, and difficulty.
Player::Player()
    : hp(0), maxHp(0), block(0), energy(0), maxEnergy(0),
      tempAttackBonus(0), combatAttackBonus(0),
      relicWarriorBlade(false), relicMagicPotion(false),
      relicLifeAmulet(false), relicEnergyCrystal(false),
      attackPlayedThisTurn(0), difficulty(0) {}

// Initialize the player based on the selected difficulty.
void Player::init(int diff) {
    difficulty = diff;
    double hpScale = DIFFICULTY_HP_SCALE[diff];

    // Scale max HP by difficulty.
    maxHp = (int)(STARTING_MAX_HP * hpScale);
    if (maxHp < 10) maxHp = 10;

    hp = maxHp;
    block = 0;
    maxEnergy = STARTING_ENERGY;
    energy = maxEnergy;

    // Reset attack bonuses and turn counters.
    tempAttackBonus = 0;
    combatAttackBonus = 0;
    attackPlayedThisTurn = 0;

    // Clear the player's hand.
    hand.clear();

    // Reset all relic effects.
    relicWarriorBlade = false;
    relicMagicPotion = false;
    relicLifeAmulet = false;
    relicEnergyCrystal = false;
}

// Start a new turn by resetting block, energy, and temporary bonuses.
void Player::startTurn() {
    block = 0;
    energy = maxEnergy;
    tempAttackBonus = 0;
    attackPlayedThisTurn = 0;

    // Draw normal cards, plus extra cards if Magic Potion is active.
    int drawCount = HAND_SIZE;
    if (relicMagicPotion) drawCount += 2;
    drawCards(drawCount);
}

// End the turn and discard all cards in hand.
void Player::endTurn() {
    hand.clear();   // discard all cards in hand
}

// Draw random cards from the global card pool.
void Player::drawCards(int num) {
    if (globalCardPool.empty()) {
        cout << "Global card pool is empty! Cannot draw.\n";
        return;
    }
    for (int i = 0; i < num; ++i) {
        int idx = rand() % globalCardPool.size();
        CardID drawn = globalCardPool[idx];
        hand.push_back(drawn);
    }
}

// Take damage after block absorbs as much as possible.
void Player::takeDamage(int dmg) {
    if (dmg <= 0) return;
    if (block >= dmg) {
        block -= dmg;
        cout << "Block absorbed all " << dmg << " damage.\n";
    } else {
        int remaining = dmg - block;
        block = 0;
        hp -= remaining;
        if (hp < 0) hp = 0;
        cout << "Took " << remaining << " damage, HP: " << hp << "/" << maxHp << "\n";
    }
}

// Add block to reduce future incoming damage.
void Player::addBlock(int amount) {
    block += amount;
    cout << "Gained " << amount << " block, total block: " << block << "\n";
}

// Heal the player without exceeding max HP.
void Player::heal(int amount) {
    if (amount <= 0) return;
    hp += amount;
    if (hp > maxHp) hp = maxHp;
    cout << "Healed " << amount << " HP, now " << hp << "/" << maxHp << "\n";
}

// Deal damage to an enemy using base damage and attack bonuses.
void Player::dealDamageTo(Enemy& enemy, int baseDamage) {
    int totalBonus = tempAttackBonus + combatAttackBonus;

    // Warrior's Blade adds bonus damage to the first attack each turn.
    if (relicWarriorBlade && attackPlayedThisTurn == 0) {
        totalBonus += 2;
        cout << "[Warrior's Blade] First attack this turn +2 damage!\n";
    }

    int actualDamage = baseDamage + totalBonus;
    if (actualDamage < 0) actualDamage = 0;
    enemy.hp -= actualDamage;
    if (enemy.hp < 0) enemy.hp = 0;
    cout << "Dealt " << actualDamage << " damage (base " << baseDamage << " + bonus " << totalBonus << ").\n";
    attackPlayedThisTurn++;
}

// Add a specific card directly to the player's hand.
void Player::addCardToHand(CardID cardId) {
    hand.push_back(cardId);
    cout << "Card " << getCardById(cardId).name << " added directly to hand.\n";
}

// Apply the effect of a relic to the player.
void Player::applyRelic(RelicID relic) {
    switch (relic) {
        case RELIC_WARRIOR_BLADE:
            relicWarriorBlade = true;
            cout << "Obtained relic: Warrior's Blade (first attack each turn +2 damage)\n";
            break;

        case RELIC_MAGIC_POTION:
            relicMagicPotion = true;
            cout << "Obtained relic: Magic Potion (draw 2 extra cards at combat start)\n";
            break;

        case RELIC_LIFE_AMULET:
            relicLifeAmulet = true;
            cout << "Obtained relic: Life Amulet (heal 3 HP after each combat)\n";
            break;

        case RELIC_ENERGY_CRYSTAL:
            relicEnergyCrystal = true;
            maxEnergy += 1;
            cout << "Obtained relic: Energy Crystal (max energy +1)\n";
            break;

        default:
            break;
    }
}

// Reset combat-related values at the start of combat.
void Player::startCombat() {
    combatAttackBonus = 0;
    attackPlayedThisTurn = 0;
}

// Apply end-of-combat effects and reset combat bonuses.
void Player::endCombat() {
    if (relicLifeAmulet) {
        heal(3);
        cout << "Life Amulet restored 3 HP.\n";
    }
    combatAttackBonus = 0;
}

// Print the player's current HP, block, and energy.
void Player::printStatus() const {
    cout << "HP: " << hp << "/" << maxHp
         << "  Block: " << block
         << "  Energy: " << energy << "/" << maxEnergy << "\n";
}

// Print all cards currently in the player's hand.
void Player::printHand() const {
    cout << "Hand (" << hand.size() << " cards):\n";
    
    for (size_t i = 0; i < hand.size(); ++i) {
        Card c = getCardById(hand[i]);
        cout << "  [" << i << "] " << c.name << " (" << c.cost << " energy) - " << c.description << "\n";
    }
}
