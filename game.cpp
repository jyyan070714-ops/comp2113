#include "game.h"
#include "player.h"
#include "map.h"
#include "combat.h"
#include "event.h"
#include "relic.h"
#include "save.h"
#include "flavor.h"
#include "utils.h"
#include <iostream>

using namespace std;

static void rewardCards(Player& player) {
    cout << "\n[Victory] Obtain a rare card!\n";
    if (rareCards.empty()) {
        cout << "No rare cards available.\n";
        return;
    }
    vector<int> indices;
    int rareCount = rareCards.size();
    while (indices.size() < 3 && indices.size() < (size_t)rareCount) {
        int idx = rand() % rareCount;
        bool exists = false;
        for (int i : indices) if (i == idx) { exists = true; break; }
        if (!exists) indices.push_back(idx);
    }
    cout << "Choose a card to add to your global pool:\n";
    for (size_t i = 0; i < indices.size(); ++i) {
        const Card& c = rareCards[indices[i]];
        cout << "  " << i+1 << ". " << c.name << " (" << c.cost << " energy) - " << c.description << "\n";
    }
    int choice = getIntInput(1, indices.size(), "Enter number: ");
    CardID selected = rareCards[indices[choice-1]].id;
    addCardToGlobalPool(selected);
}

static void restMenu(Player& player) {
    cout << "\n===== Rest Site =====\n";
    cout << "1. Heal (restore 15 HP)\n";
    int choice = getIntInput(1, 1, "Choose: ");
    if (choice == 1) {
        player.heal(15);
    }
}

void newGame() {
    cout << "\n===== New Game =====\n";
    cout << "Select difficulty:\n";
    cout << "1. Easy\n";
    cout << "2. Normal\n";
    cout << "3. Hard\n";
    int diffChoice = getIntInput(1, 3, "Enter: ");
    int difficulty = diffChoice - 1;

    initGlobalCardPool();   // reset to basic+advanced only

    Player player;
    player.init(difficulty);
    vector<Node> route = getRoute();
    int currentNode = 0;
    bool gameComplete = false;

    for (size_t i = 0; i < route.size(); ++i) {
        currentNode = i;
        Node& node = route[i];
        showFlavorText(node.type);
        switch (node.type) {
            case FIGHT: {
                Enemy* enemy = new Enemy(createEnemy((EnemyID)node.enemyId, player.difficulty));
                bool win = combat(player, *enemy, node.type);
                delete enemy;
                if (!win) {
                    cout << "Game over.\n";
                    return;
                }
                rewardCards(player);
                break;
            }
            case ELITE: {
                Enemy* enemy = new Enemy(createEnemy((EnemyID)node.enemyId, player.difficulty));
                bool win = combat(player, *enemy, node.type);
                delete enemy;
                if (!win) {
                    cout << "Game over.\n";
                    return;
                }
                rewardCards(player);
                break;
            }
            case EVENT:
                triggerRandomEvent(player);
                break;
            case REST:
                restMenu(player);
                break;
            case BOSS: {
                Enemy* enemy = new Enemy(createEnemy((EnemyID)node.enemyId, player.difficulty));
                bool win = combat(player, *enemy, node.type);
                delete enemy;
                if (!win) {
                    cout << "Game over.\n";
                    return;
                }
                giveRandomRelic(player);
                gameComplete = true;
                break;
            }
        }
        saveGame(player, currentNode + 1, gameComplete);
        if (node.type != BOSS) {
            waitForEnter();
        }
    }
    cout << "\n*** Congratulations! You have completed the game! ***\n";
}

void continueGame() {
    Player player;
    int currentNode = 0;
    bool gameComplete = false;
    if (!loadGame(player, currentNode, gameComplete)) {
        cout << "Failed to load save. Please start a new game.\n";
        return;
    }
    if (gameComplete) {
        cout << "You have already completed the game. Start a new game.\n";
        return;
    }
    // Reset global pool to basic+advanced (since we don't save extra cards)
    initGlobalCardPool();

    vector<Node> route = getRoute();
    cout << "Resuming from node " << currentNode+1 << ".\n";
    for (size_t i = currentNode; i < route.size(); ++i) {
        Node& node = route[i];
        showFlavorText(node.type);
        switch (node.type) {
            case FIGHT: {
                Enemy* enemy = new Enemy(createEnemy((EnemyID)node.enemyId, player.difficulty));
                bool win = combat(player, *enemy, node.type);
                delete enemy;
                if (!win) {
                    cout << "Game over.\n";
                    return;
                }
                rewardCards(player);
                break;
            }
            case ELITE: {
                Enemy* enemy = new Enemy(createEnemy((EnemyID)node.enemyId, player.difficulty));
                bool win = combat(player, *enemy, node.type);
                delete enemy;
                if (!win) {
                    cout << "Game over.\n";
                    return;
                }
                rewardCards(player);
                break;
            }
            case EVENT:
                triggerRandomEvent(player);
                break;
            case REST:
                restMenu(player);
                break;
            case BOSS: {
                Enemy* enemy = new Enemy(createEnemy((EnemyID)node.enemyId, player.difficulty));
                bool win = combat(player, *enemy, node.type);
                delete enemy;
                if (!win) {
                    cout << "Game over.\n";
                    return;
                }
                giveRandomRelic(player);
                gameComplete = true;
                break;
            }
        }
        saveGame(player, (int)i + 1, gameComplete);
        if (node.type != BOSS) waitForEnter();
    }
    cout << "\n*** Congratulations! You have completed the game! ***\n";
}

void mainMenu() {
    initRandom();
    while (true) {
        cout << "\n===== Slay the Spire Lite =====\n";
        cout << "1. New Game\n";
        cout << "2. Continue Game\n";
        cout << "3. Exit\n";
        int choice = getIntInput(1, 3, "Choose: ");
        switch (choice) {
            case 1: newGame(); break;
            case 2: continueGame(); break;
            case 3: cout << "Goodbye!\n"; return;
        }
    }
}

void runGame() {
    mainMenu();
}
