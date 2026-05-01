#ifndef EVENT_H
#define EVENT_H

#include "common.h"

class Player;

void triggerRandomEvent(Player& player);
void eventShrine(Player& player);
void eventTrap(Player& player);
void eventMerchant(Player& player);
void eventCampfire(Player& player);
void eventCursedWell(Player& player);
void eventEliteGhost(Player& player);

#endif // EVENT_H