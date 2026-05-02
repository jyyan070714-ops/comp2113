#pragma once
#include "common.h"
#include "player.h"
#include "enemy.h"

bool combat(Player& player, Enemy& enemy, NodeType nodeType);
void playerTurn(Player& player, Enemy& enemy);
void displayCombatStatus(const Player& player, const Enemy& enemy, NodeType nodeType);
