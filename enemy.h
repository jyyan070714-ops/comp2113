#pragma once

#include "common.h"
#include <string>

class Player;

struct Enemy {
    std::string name;
    int intentDamage;
    int hp;
    int attack;
    int specialCounter;
    int baseAttack;
 };


Enemy createEnemy(EnemyID id, int difficulty);
void enemyAction(Enemy& e, Player& p, NodeType type);
void normalEnemyAction(Enemy& e, Player& p);
void eliteEnemyAction(Enemy& e, Player& p);
void bossEnemyAction(Enemy& e, Player& p);
void printEnemyIntent(const Enemy& e, NodeType type);
void rollEnemyIntent(Enemy& e, NodeType type);
