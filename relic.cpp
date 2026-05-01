#include "relic.h"
#include "player.h"
#include <iostream>

using namespace std;

// Return the display name of a relic.
string getRelicName(RelicID relicId) {
    switch (relicId) {
    case RELIC_WARRIOR_BLADE: return "Warrior's Blade";
    case RELIC_MAGIC_POTION:  return "Magic Potion";
    case RELIC_LIFE_AMULET:   return "Life Amulet";
    case RELIC_ENERGY_CRYSTAL:return "Energy Crystal";
    default:                  return "Unknown Relic";
    }
}

// Return the description text for a relic.
string getRelicDescription(RelicID relicId) {
    switch (relicId) {
    case RELIC_WARRIOR_BLADE: return "First attack each turn deals +2 damage";
    case RELIC_MAGIC_POTION:  return "Draw 2 extra cards at combat start";
    case RELIC_LIFE_AMULET:   return "Heal 3 HP after each combat";
    case RELIC_ENERGY_CRYSTAL:return "Max energy +1";
    default:                  return "";
    }
}

// Apply a relic to the player and print its information.
void applyRelicById(Player& player, RelicID relicId) {
    player.applyRelic(relicId);
    cout << "Obtained relic: " << getRelicName(relicId) << " - " << getRelicDescription(relicId) << "\n";
}

// Give the player a random relic.
void giveRandomRelic(Player& player) {
    int r = rand() % TOTAL_RELICS;
    RelicID relic = static_cast<RelicID>(r);
    applyRelicById(player, relic);
}
