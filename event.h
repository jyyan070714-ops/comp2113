#ifndef EVENT_H
#define EVENT_H

#include "common.h"

class Player;

// What it does: selects and runs one random event during the adventure.
// Inputs: a Player reference used to apply event effects.
// Outputs: none directly; may change the player's state and print event text.
void triggerRandomEvent(Player& player);

// What it does: handles the Ancient Shrine event and the player's choice there.
// Inputs: a Player reference used for healing or other event effects.
// Outputs: none directly; may change the player's state, update the card pool, and print results.
void eventShrine(Player& player);

// What it does: handles the Hidden Trap event and applies its damage effect.
// Inputs: a Player reference used to subtract HP from the player.
// Outputs: none directly; updates the player's HP and prints the event outcome.
void eventTrap(Player& player);

// What it does: handles the Wandering Merchant event and processes trade choices.
// Inputs: a Player reference used for HP payment and trade checks.
// Outputs: none directly; may change the player's HP, update the global card pool, and print results.
void eventMerchant(Player& player);

// What it does: handles the Campfire Gathering event, including healing and card upgrades.
// Inputs: a Player reference used for healing decisions.
// Outputs: none directly; may heal the player, upgrade a card, and print results.
void eventCampfire(Player& player);

// What it does: handles the Cursed Well event and the player's sacrifice choice.
// Inputs: a Player reference used for HP checks and damage.
// Outputs: none directly; may change the player's HP, add a card to the pool, and print results.
void eventCursedWell(Player& player);

// What it does: handles the Elite Ghost event and the player's response.
// Inputs: a Player reference used for HP checks and damage.
// Outputs: none directly; may change the player's HP, add a rare card to the pool, and print results.
void eventEliteGhost(Player& player);

#endif // EVENT_H