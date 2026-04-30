#ifndef CARD_H
#define CARD_H

#include "common.h"

// A single card's properties
struct Card {
    CardID id;          // Unique identifier for this card (matches the CardID enum)
    string name;
    int cost;           // Energy costs to use this card (0-2)
    CardType type;      // Category: attack or skill
    int value;          // Nemeric effect: (damage dealt or blocl gained)
    int draw;           // Number of cards to draw (if none then 0)
    int heal;           // HP restored when use (if none then 0)
    bool multiHit;      // True if this card hits multiple times (Double strikes)
    int hitCount;       // Number of hits if multiHit is true
    string description; // Description shown for player
};

// Master list of every card in the game, indexed by their CardID values
extern const vector<Card> allCards;

// A rare-tier cards subset for rare reward pools
extern const vector<Card> rareCards;

// A Getter returns the Card struct matching the given CardID; defaults to allCards[0] if not found.
Card getCardById(CardID id);

// A Getter returns the upgradeed (+) version of a card's id; returns the same id of no upgrade
CardID getUpgradedVersion(CardID id);

// Return true if the given CardID belongs to the rare card pool
bool isRareCard(CardID id);

//Exeutes effect of the card
void playCard(Player& player, Enemy& enemy, const Card& card);

#endif 
