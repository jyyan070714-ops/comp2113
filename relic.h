#ifndef RELIC_H
#define RELIC_H

#include "common.h"

class Player;

// Give the player a random relic.
void giveRandomRelic(Player& player);

// Apply a specific relic to the player by its ID.
void applyRelicById(Player& player, RelicID relicId);

// Get the display name of a relic.
string getRelicName(RelicID relicId);

// Get the description text of a relic.
string getRelicDescription(RelicID relicId);

#endif // RELIC_H
