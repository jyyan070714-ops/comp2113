#include "card.h"
#include "player.h"
#include "enemy.h"

// Master card database - every card and its upgraded variant
// Cards are grouped by tier and the index comments reflect their CardID enum values
const vector<Card> allCards = {
    // Basic cards (0-5)
    {STRIKE, "Strike", 1, ATTACK, 6, 0, 0, false, 0, "Deal 6 damage"},
    {DEFEND, "Defend", 1, SKILL, 5, 0, 0, false, 0, "Gain 5 block"},
    {HEAVY_STRIKE, "Heavy Strike", 2, ATTACK, 12, 0, 0, false, 0, "Deal 12 damage"},
    {IRON_WALL, "Iron Wall", 2, SKILL, 10, 0, 0, false, 0, "Gain 10 block"},
    {FOCUS, "Focus", 1, SKILL, 0, 2, 0, false, 0, "Draw 2 cards"},
    {EMERGENCY_HEAL, "Emergency Heal", 1, SKILL, 0, 0, 3, false, 0, "Heal 3 HP"},

    // Advanced cards (6-11)
    {ANGRY_STRIKE, "Angry Strike", 1, ATTACK, 4, 0, 0, false, 0, "Deal 4 damage, gain +2 attack this turn"},
    {TACTICIAN, "Tactician", 1, SKILL, 0, 1, 0, false, 0, "Draw 1 card, gain 1 energy"},
    {DOUBLE_STRIKE, "Double Strike", 2, ATTACK, 5, 0, 0, true, 2, "Deal 5 damage twice"},
    {FLAME_SHIELD, "Flame Shield", 1, SKILL, 4, 0, 0, false, 0, "Gain 4 block, deal 3 damage"},
    {LIFE_DRAIN, "Life Drain", 2, ATTACK, 8, 0, 8, false, 0, "Deal 8 damage, heal 8 HP"},
    {PREPARATION, "Preparation", 0, SKILL, 0, 1, 0, false, 0, "Draw 1 card"},

    // Power cards (12-13)
    {POWER_POTION, "Power Potion", 1, SKILL, 0, 0, 0, false, 0, "Permanent +3 attack this combat"},
    {LIFE_CONTRACT, "Life Contract", 2, SKILL, 0, 0, 0, false, 0, "Increase max HP by 5, heal 5"},

    // Rare cards (14-18)
    {METEOR, "Meteor", 2, ATTACK, 18, 0, 0, false, 0, "Deal 18 damage"},
    {HOLY_BARRIER, "Holy Barrier", 2, SKILL, 15, 1, 0, false, 0, "Gain 15 block, draw 1 card"},
    {FURY_COMBO, "Fury Combo", 2, ATTACK, 6, 0, 0, true, 3, "Deal 6 damage three times"},
    {SOUL_DRAIN, "Soul Drain", 2, ATTACK, 10, 0, 8, false, 0, "Deal 10 damage, heal 8 HP"},
    {TIME_WARP, "Time Warp", 1, SKILL, 0, 3, 0, false, 0, "Draw 3 cards, gain 1 energy"},

    // Upgraded cards (partial)
    {STRIKE_PLUS, "Strike+", 1, ATTACK, 9, 0, 0, false, 0, "Deal 9 damage"},
    {DEFEND_PLUS, "Defend+", 1, SKILL, 8, 0, 0, false, 0, "Gain 8 block"},
    {HEAVY_STRIKE_PLUS, "Heavy Strike+", 2, ATTACK, 16, 0, 0, false, 0, "Deal 16 damage"},
    {IRON_WALL_PLUS, "Iron Wall+", 2, SKILL, 13, 0, 0, false, 0, "Gain 13 block"},
    {FOCUS_PLUS, "Focus+", 1, SKILL, 0, 3, 0, false, 0, "Draw 3 cards"},
    {EMERGENCY_HEAL_PLUS, "Emergency Heal+", 1, SKILL, 0, 0, 5, false, 0, "Heal 5 HP"},
    {ANGRY_STRIKE_PLUS, "Angry Strike+", 1, ATTACK, 6, 0, 0, false, 0, "Deal 6 damage, gain +3 attack this turn"},
    {TACTICIAN_PLUS, "Tactician+", 1, SKILL, 0, 2, 0, false, 0, "Draw 2 cards, gain 1 energy"},
    {DOUBLE_STRIKE_PLUS, "Double Strike+", 2, ATTACK, 7, 0, 0, true, 2, "Deal 7 damage twice"},
    {FLAME_SHIELD_PLUS, "Flame Shield+", 1, SKILL, 6, 0, 0, false, 0, "Gain 6 block, deal 5 damage"},
    {LIFE_DRAIN_PLUS, "Life Drain+", 2, ATTACK, 11, 0, 11, false, 0, "Deal 11 damage, heal 11 HP"},
    {PREPARATION_PLUS, "Preparation+", 0, SKILL, 0, 2, 0, false, 0, "Draw 2 cards"},
    {POWER_POTION_PLUS, "Power Potion+", 1, SKILL, 0, 0, 0, false, 0, "Permanent +5 attack this combat"},
    {LIFE_CONTRACT_PLUS, "Life Contract+", 2, SKILL, 0, 0, 0, false, 0, "Increase max HP by 8, heal 8"},
    {METEOR_PLUS, "Meteor+", 2, ATTACK, 24, 0, 0, false, 0, "Deal 24 damage"},
    {HOLY_BARRIER_PLUS, "Holy Barrier+", 2, SKILL, 20, 2, 0, false, 0, "Gain 20 block, draw 2 cards"},
    {FURY_COMBO_PLUS, "Fury Combo+", 2, ATTACK, 8, 0, 0, true, 3, "Deal 8 damage three times"},
    {SOUL_DRAIN_PLUS, "Soul Drain+", 2, ATTACK, 14, 0, 12, false, 0, "Deal 14 damage, heal 12 HP"},
    {TIME_WARP_PLUS, "Time Warp+", 1, SKILL, 0, 4, 0, false, 0, "Draw 4 cards, gain 2 energy"}
};

// Rare card pool
const vector<Card> rareCards = {
    {METEOR, "Meteor", 2, ATTACK, 18, 0, 0, false, 0, "Deal 18 damage"},
    {HOLY_BARRIER, "Holy Barrier", 2, SKILL, 15, 1, 0, false, 0, "Gain 15 block, draw 1 card"},
    {FURY_COMBO, "Fury Combo", 2, ATTACK, 6, 0, 0, true, 3, "Deal 6 damage three times"},
    {SOUL_DRAIN, "Soul Drain", 2, ATTACK, 10, 0, 8, false, 0, "Deal 10 damage, heal 8 HP"},
    {TIME_WARP, "Time Warp", 1, SKILL, 0, 3, 0, false, 0, "Draw 3 cards, gain 1 energy"}
};

// Looks up a card by its CardID in allCards and returns the matching Card struct or allCards[0] as a fallback if not found
Card getCardById(CardID id) {
    for (const auto& card : allCards) {
        if (card.id == id) return card;
    }
    return allCards[0];
}

// Maps each base card to its upgraded (+) version
// Returns the same ID unchanged if no upgrade
CardID getUpgradedVersion(CardID id) {
    switch (id) {
    case STRIKE: return STRIKE_PLUS;
    case DEFEND: return DEFEND_PLUS;
    case HEAVY_STRIKE: return HEAVY_STRIKE_PLUS;
    case IRON_WALL: return IRON_WALL_PLUS;
    case FOCUS: return FOCUS_PLUS;
    case EMERGENCY_HEAL: return EMERGENCY_HEAL_PLUS;
    case ANGRY_STRIKE: return ANGRY_STRIKE_PLUS;
    case TACTICIAN: return TACTICIAN_PLUS;
    case DOUBLE_STRIKE: return DOUBLE_STRIKE_PLUS;
    case FLAME_SHIELD: return FLAME_SHIELD_PLUS;
    case LIFE_DRAIN: return LIFE_DRAIN_PLUS;
    case PREPARATION: return PREPARATION_PLUS;
    case POWER_POTION: return POWER_POTION_PLUS;
    case LIFE_CONTRACT: return LIFE_CONTRACT_PLUS;
    case METEOR: return METEOR_PLUS;
    case HOLY_BARRIER: return HOLY_BARRIER_PLUS;
    case FURY_COMBO: return FURY_COMBO_PLUS;
    case SOUL_DRAIN: return SOUL_DRAIN_PLUS;
    case TIME_WARP: return TIME_WARP_PLUS;
    default: return id;
    }
}

// Checks whether a CardID belongs to the rare tier by scanning rareCards
bool isRareCard(CardID id) {
    for (const auto& rc : rareCards) {
        if (rc.id == id) return true;
    }
    return false;
}

// Applyies a card's effect
// Each case handles one card and its upgradeed viriant
void playCard(Player& player, Enemy& enemy, const Card& card) {
    switch (card.id) {

    // basic attack and block cards    
    case STRIKE:
    case STRIKE_PLUS:
        player.dealDamageTo(enemy, card.value);
        break;
    case DEFEND:
    case DEFEND_PLUS:
        player.addBlock(card.value);
        break;
    case HEAVY_STRIKE:
    case HEAVY_STRIKE_PLUS:
        player.dealDamageTo(enemy, card.value);
        break;
    case IRON_WALL:
    case IRON_WALL_PLUS:
        player.addBlock(card.value);
        break;

    // Draw and heal basics    
    case FOCUS:
    case FOCUS_PLUS:
        player.drawCards(card.draw);
        break;
    case EMERGENCY_HEAL:
    case EMERGENCY_HEAL_PLUS:
        player.heal(card.heal);
        break;

    // Advanced cards
    // Angry Strikes: deal damage + a temporary per-turn attack bonus    
    case ANGRY_STRIKE:
    case ANGRY_STRIKE_PLUS:
        player.dealDamageTo(enemy, card.value);
        player.tempAttackBonus += (card.id == ANGRY_STRIKE_PLUS ? 3 : 2);
        cout << "Angry Strike: +" << (card.id == ANGRY_STRIKE_PLUS ? 3 : 2) << " attack this turn.\n";
        break;

    // Draw cards and immediately refund 1 energy    
    case TACTICIAN:
    case TACTICIAN_PLUS:
        player.drawCards(card.draw);
        player.energy += 1;
        cout << "Tactician: Gain 1 energy.\n";
        break;

    // Hits the enemy twice    
    case DOUBLE_STRIKE:
    case DOUBLE_STRIKE_PLUS:
        for (int i = 0; i < 2; ++i) {
            player.dealDamageTo(enemy, card.value);
        }
        break;

    // Gain block and deal a small amount of damage    
    case FLAME_SHIELD:
    case FLAME_SHIELD_PLUS:
        player.addBlock(card.value);
        player.dealDamageTo(enemy, (card.id == FLAME_SHIELD_PLUS ? 5 : 3));
        break;

    // Deal damage and heal the same amount    
    case LIFE_DRAIN:
    case LIFE_DRAIN_PLUS:
        player.dealDamageTo(enemy, card.value);
        player.heal(card.heal);
        break;

    // Zero-cost card draw    
    case PREPARATION:
    case PREPARATION_PLUS:
        player.drawCards(card.draw);
        break;

    // Power cards
    // Increases attack for the rest of this combat
    case POWER_POTION:
    case POWER_POTION_PLUS:
        player.combatAttackBonus += (card.id == POWER_POTION_PLUS ? 5 : 3);
        cout << "Power Potion: +" << (card.id == POWER_POTION_PLUS ? 5 : 3) << " attack this combat (total +" << player.combatAttackBonus << ").\n";
        break;

    // Increases max HP permanently and heals the same amount    
    case LIFE_CONTRACT:
    case LIFE_CONTRACT_PLUS: {
        int gain = (card.id == LIFE_CONTRACT_PLUS ? 8 : 5);
        player.maxHp += gain;
        player.hp += gain;
        if (player.hp > player.maxHp) player.hp = player.maxHp;  // cap at new max
        cout << "Life Contract: Max HP +" << gain << ", heal " << gain << " (now " << player.hp << "/" << player.maxHp << ").\n";
        break;
    }

    // Rare cards
    // High single-hit damage
    case METEOR:
    case METEOR_PLUS:
        player.dealDamageTo(enemy, card.value);
        break;

    // Large block and card draw    
    case HOLY_BARRIER:
    case HOLY_BARRIER_PLUS:
        player.addBlock(card.value);
        player.drawCards(card.draw);
        break;

    // Hit the enemy three times    
    case FURY_COMBO:
    case FURY_COMBO_PLUS:
        for (int i = 0; i < 3; ++i) {
            player.dealDamageTo(enemy, card.value);
        }
        break;

    // Deal damage and heal a fixed amount    
    case SOUL_DRAIN:
    case SOUL_DRAIN_PLUS:
        player.dealDamageTo(enemy, card.value);
        player.heal(card.heal);
        break;

    // Draw cards and gain energy    
    case TIME_WARP:
    case TIME_WARP_PLUS:
        player.drawCards(card.draw);
        player.energy += (card.id == TIME_WARP_PLUS ? 2 : 1);
        cout << "Time Warp: Gain " << (card.id == TIME_WARP_PLUS ? 2 : 1) << " energy.\n";
        break;
    default:
        break;
    }
}
