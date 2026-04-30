#include "enemy.h"
#include "player.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Enemy createEnemy(EnemyID id, int difficulty) {
    Enemy newEnemy;
    
    double hpScale = DIFFICULTY_ENEMY_HP_SCALE[difficulty];
    double dmgScale = DIFFICULTY_ENEMY_DMG_SCALE[difficulty];

    switch (id) {
    case ENEMY_SLIME:
        newEnemy.name = "Small Slime";
        newEnemy.hp = (int)(20 * hpScale);
        newEnemy.attack = (int)(6 * dmgScale);
        newEnemy.specialCounter = 0;
        newEnemy.baseAttack = (int)(6 * dmgScale);
        newEnemy.intentDamage = 0;
        break;
        
    case ENEMY_GOBLIN:
        newEnemy.name = "Goblin Marauder";
        newEnemy.hp = (int)(35 * hpScale);
        newEnemy.attack = (int)(9 * dmgScale);
        newEnemy.specialCounter = 0;
        newEnemy.baseAttack = (int)(9 * dmgScale);
        newEnemy.intentDamage = 0;
        break;
        
    case ENEMY_GOBLIN_BOSS:
        newEnemy.name = "Goblin Boss";
        newEnemy.hp = (int)(55 * hpScale);
        newEnemy.attack = (int)(12 * dmgScale);
        newEnemy.specialCounter = 0;
        newEnemy.baseAttack = (int)(12 * dmgScale);
        newEnemy.intentDamage = 0;
        break;
        
    default:
        newEnemy.name = "Unknown Enemy";
        newEnemy.hp = 10;
        newEnemy.attack = 5;
        newEnemy.specialCounter = 0;
        newEnemy.baseAttack = 5;
        newEnemy.intentDamage = 0;
        break;
    }

    return newEnemy;
}

void enemyAction(Enemy& e, Player& p, NodeType type) {
    if (type == FIGHT) {
        normalEnemyAction(e, p);
    }
    else if (type == ELITE) {
        eliteEnemyAction(e, p);
    }
    else if (type == BOSS) {
        bossEnemyAction(e, p);
    }
    else {
        normalEnemyAction(e, p);
    }
}

void normalEnemyAction(Enemy& e, Player& p) {
    cout << e.name << " attacks for " << e.intentDamage << " damage!\n";
    p.takeDamage(e.intentDamage);
}

void eliteEnemyAction(Enemy& e, Player& p) {
    e.specialCounter++;

    if (e.specialCounter % 2 == 0) {
        cout << e.name << " uses Plunder! Deals " << e.intentDamage << " damage and steals 1 energy.\n";
        p.takeDamage(e.intentDamage);
        if (p.energy > 0) {
            p.energy--;
            cout << "Your energy was stolen! Remaining energy: " << p.energy << "\n";
        }
        else {
            cout << "You have no energy to steal.\n";
        }
    }
    else {
        cout << e.name << " attacks for " << e.intentDamage << " damage!\n";
        p.takeDamage(e.intentDamage);
    }
}

void bossEnemyAction(Enemy& e, Player& p) {
    e.specialCounter++;
    if (e.specialCounter % 3 == 0) {
        cout << e.name << " enrages! Attack power increased!\n";
    }
    
    cout << e.name << " attacks for " << e.intentDamage << " damage!\n";
    p.takeDamage(e.intentDamage);
}

void rollEnemyIntent(Enemy& e, NodeType type) {
    int nextCounter = e.specialCounter + 1;
    int baseDmg = e.attack;

    if (type == BOSS && nextCounter % 3 == 0) {
        baseDmg += 6;
    }

    int roll = baseDmg + (rand() % 5 - 2);
    if (roll < 0) {
        roll = 0;
    }
    e.intentDamage = roll;
}

void printEnemyIntent(const Enemy& e, NodeType type) {
    cout << "   [Enemy Intent]: ";
    int nextCounter = e.specialCounter + 1;

    if (type == ELITE && nextCounter % 2 == 0) {
        cout << "Plans to Plunder! Will deal " << e.intentDamage << " damage and steal 1 energy.\n";
    }
    else if (type == BOSS && nextCounter % 3 == 0) {
        cout << "Plans a MASSIVE attack for " << e.intentDamage << " damage!\n";
    }
    else {
        cout << "Plans to attack for " << e.intentDamage << " damage.\n";
    }
}
