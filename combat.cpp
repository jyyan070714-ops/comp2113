#include "combat.h"
#include "card.h"
#include "ascii_art.h"
#include "flavor.h"
#include <iostream>
#include <string>

using namespace std;

void displayCombatStatus(const Player& player, const Enemy& enemy, NodeType nodeType) {
    cout << "\n========== COMBAT ==========\n";
    printPlayerArt();
    player.printStatus();
    cout << "\n   VS\n\n";
    printEnemyArt(enemy.name);
    cout << "[" << enemy.name << "] HP: " << enemy.hp << "\n";
    printEnemyIntent(enemy, nodeType);
    cout << "============================\n";
 }

void playerTurn(Player& player, Enemy& enemy) {
    player.startTurn();
    bool turnEnd = false;

    while (!turnEnd) {
        displayCombatStatus(player, enemy, FIGHT);
        player.printHand();
        cout << "\nChoose action:\n";
        cout << "  [index] Play card\n";
        cout << "  [r] End turn\n";
        cout << "Enter: ";

        string input;
        cin >> input;

        if (input == "r" || input == "R") {
            turnEnd = true;
            break;
        }

        int idx = -1;
        if (input.length() == 1 && input[0] >= '0' && input[0] <= '9') {
            idx = input[0] - '0';
        } else if (input.length() == 2 && input[0] >= '0' && input[0] <= '9' && input[1] >= '0' && input[1] <= '9') {
            idx = (input[0] - '0') * 10 + (input[1] - '0');
        }

        if (idx < 0 || idx >= (int)player.hand.size()) {
            cout << "Invalid card index.\n";
            continue;
        }

        CardID cid = player.hand[idx];
        Card card = getCardById(cid);
        if (player.energy < card.cost) {
            cout << "Not enough energy! Need " << card.cost << " energy.\n";
            continue;
        }

        player.energy -= card.cost;
        playCard(player, enemy, card);

        player.hand.erase(player.hand.begin() + idx);

        if (enemy.hp <= 0) {
            cout << "Enemy defeated!\n";
            turnEnd = true;
            break;
        }
    }
    player.endTurn();
 }

bool combat(Player& player, Enemy& enemy, NodeType nodeType) {
    player.startCombat();
    cout << "\n===== COMBAT START =====\n";
    showFlavorText(nodeType);

    int roundCounter = 1;

    while (true) {
        cout << "\n===== combat " << roundCounter << " =====\n";

        rollEnemyIntent(enemy, nodeType);

        playerTurn(player, enemy);
        if (enemy.hp <= 0) {
            cout << "Victory!\n";
            player.endCombat();
            return true;
        }
        if (player.hp <= 0) {
            cout << "You have been defeated...\n";
            return false;
        }

        cout << "\n--- Enemy Turn ---\n";
        enemyAction(enemy, player, nodeType);
        if (player.hp <= 0) {
            cout << "You have been defeated...\n";
            return false;
        }

        roundCounter++;
    }
 }
