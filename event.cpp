#include "event.h"
#include "player.h"
#include "card.h"
#include <iostream>
#include <cstdlib>

using namespace std;

static void showEventTitle(const string& title) {
    cout << "\n========== \"" << title << "\" ==========\n";
}

void eventShrine(Player& player) {
    showEventTitle("Ancient Shrine");
    cout << "You find an ancient shrine with a glowing gem.\n";
    cout << "1. Take the gem (gain a random rare card)\n";
    cout << "2. Pray (heal 10 HP)\n";
    cout << "3. Leave\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        int idx = rand() % rareCards.size();
        CardID newCard = rareCards[idx].id;
        addCardToGlobalPool(newCard);
        cout << "You obtained card: " << getCardById(newCard).name << " added to global pool!\n";
    } else if (choice == 2) {
        player.heal(10);
        cout << "You feel a warm energy. HP restored.\n";
    } else {
        cout << "You leave the shrine. Nothing happens.\n";
    }
}

void eventTrap(Player& player) {
    showEventTitle("Hidden Trap");
    int damage = 6;
    cout << "You step on a hidden trap and lose " << damage << " HP.\n";
    player.takeDamage(damage);
}

void eventMerchant(Player& player) {
    showEventTitle("Wandering Merchant");
    cout << "A mysterious merchant shows you some cards.\n";
    cout << "1. Pay 8 HP for a rare card\n";
    cout << "2. Pay 3 HP for a common card\n";
    cout << "3. Decline\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        if (player.hp > 8) {
            player.takeDamage(8);
            int idx = rand() % rareCards.size();
            CardID newCard = rareCards[idx].id;
            addCardToGlobalPool(newCard);
            cout << "You received: " << getCardById(newCard).name << " added to global pool.\n";
        } else {
            cout << "Not enough HP to trade.\n";
        }
    } else if (choice == 2) {
        if (player.hp > 3) {
            player.takeDamage(3);
            // Common card: from basic+advanced (excluding rare/power)
            vector<CardID> normalCards;
            for (const auto& c : allCards) {
                if (!isRareCard(c.id) && c.id < 100 && c.id != POWER_POTION && c.id != LIFE_CONTRACT) {
                    normalCards.push_back(c.id);
                }
            }
            if (!normalCards.empty()) {
                int idx = rand() % normalCards.size();
                CardID newCard = normalCards[idx];
                addCardToGlobalPool(newCard);
                cout << "You received: " << getCardById(newCard).name << " added to global pool.\n";
            } else {
                cout << "No common cards available.\n";
            }
        } else {
            cout << "Not enough HP to trade.\n";
        }
    } else {
        cout << "You decline the trade.\n";
    }
}

void eventCampfire(Player& player) {
    showEventTitle("Campfire Gathering");
    cout << "A group of friendly adventurers shares food.\n";
    cout << "1. Eat together (heal 8 HP)\n";
    cout << "2. Forge weapon (Upgrade a card)\n";
    cout << "3. Leave\n";
    cout << "Choice: ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        player.heal(8);
        cout << "You eat with them. HP restored.\n";
    } else if (choice == 2) {
        if (globalCardPool.empty()) {
            cout << "You have no cards in the pool to upgrade!\n";
        } else {
            cout << "\nChoose a card to upgrade:\n";
            for (size_t i = 0; i < globalCardPool.size(); ++i) {
                Card c = getCardById(globalCardPool[i]);
                cout << "  " << i + 1 << ". " << c.name << " - " << c.description << "\n";
            }
            
            int cardChoice;
            cout << "Enter number: ";
            cin >> cardChoice;

            if (cardChoice >= 1 && cardChoice <= (int)globalCardPool.size()) {
                CardID oldId = globalCardPool[cardChoice - 1];
                CardID newId = getUpgradedVersion(oldId);

                if (oldId == newId) {
                    cout << "This card cannot be upgraded further.\n";
                } else {
                    globalCardPool[cardChoice - 1] = newId;
                    Card newCard = getCardById(newId);

                    cout << "\n[Upgrade Successful!]\n";
                    cout << "Card upgraded to: " << newCard.name << "\n";
                    cout << "New Description:  " << newCard.description << "\n";
                    cout << "New Cost:         " << newCard.cost << " energy\n";
                }
            } else {
                cout << "Invalid choice. You wasted your time at the camp.\n";
            }
        }
    } else {
        cout << "You leave the camp.\n";
    }
}

void eventCursedWell(Player& player) {
    showEventTitle("Cursed Well");
    cout << "Whispers come from the well, asking for blood or offering a card.\n";
    cout << "1. Offer blood (lose 4 HP, gain a random power card)\n";
    cout << "2. Ignore\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        if (player.hp > 4) {
            player.takeDamage(4);
            // give random power card (POWER_POTION or LIFE_CONTRACT)
            int r = rand() % 2;
            CardID powerCard = (r == 0) ? POWER_POTION : LIFE_CONTRACT;
            addCardToGlobalPool(powerCard);
            cout << "You obtained " << getCardById(powerCard).name << " added to global pool.\n";
        } else {
            cout << "Not enough HP to offer.\n";
        }
    } else {
        cout << "You leave the well.\n";
    }
}

void eventEliteGhost(Player& player) {
    showEventTitle("Elite Ghost");
    cout << "A ghost demands you prove your courage.\n";
    cout << "1. Fight (trigger a special combat - gain a rare card)\n";
    cout << "2. Sacrifice (lose 12 HP, gain a rare card)\n";
    cout << "3. Flee\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        cout << "You fight the ghost and emerge victorious!\n";
        if (!rareCards.empty()) {
            int idx = rand() % rareCards.size();
            CardID newCard = rareCards[idx].id;
            addCardToGlobalPool(newCard);
            cout << "You obtained: " << getCardById(newCard).name << " added to global pool.\n";
        } else {
            cout << "The ghost vanishes, leaving nothing.\n";
        }
    } else if (choice == 2) {
        if (player.hp > 12) {
            player.takeDamage(12);
            if (!rareCards.empty()) {
                int idx = rand() % rareCards.size();
                CardID newCard = rareCards[idx].id;
                addCardToGlobalPool(newCard);
                cout << "You sacrifice and receive: " << getCardById(newCard).name << " added to global pool.\n";
            } else {
                cout << "Nothing happens.\n";
            }
        } else {
            cout << "Not enough HP to sacrifice.\n";
        }
    } else {
        cout << "You flee. Nothing happens.\n";
    }
}

void triggerRandomEvent(Player& player) {
    int r = rand() % 6;
    switch (r) {
        case 0: eventShrine(player); break;
        case 1: eventTrap(player); break;
        case 2: eventMerchant(player); break;
        case 3: eventCampfire(player); break;
        case 4: eventCursedWell(player); break;
        case 5: eventEliteGhost(player); break;
        default: break;
    }
}
