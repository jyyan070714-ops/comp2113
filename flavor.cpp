#include "flavor.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
//descriptions of the battle scene
static const vector<string> fightFlavor = {
    "A hungry slime blocks your path, dripping with slime.",
    "Goblins sharpen their blades by the campfire. They spot you.",
    "A foul stench fills the air as a dark shadow lunges.",
    "The monster roars and charges, shaking the ground.",
    "You smell blood. A fierce beast appears ahead."
};

static const vector<string> eliteFlavor = {
    "An armored goblin marauder stands before you, eyes fierce.",
    "The elite guard growls, his weapon glinting in the dark.",
    "A powerful enemy blocks your way. You must give it your all.",
    "The air grows heavy with menace. A strong opponent awaits."
};

static const vector<string> bossFlavor = {
    "The Goblin Boss swings a giant club and roars at you!",
    "Evil energy surrounds this place. The Boss is waiting.",
    "A crushing pressure fills the air. The real fight begins.",
    "A huge shadow looms over you. The Goblin Boss appears!"
};

static const vector<string> eventFlavor = {
    "You see a strange glow ahead. Something is hidden there.",
    "An old, dusty chest sits by the roadside, smelling of mold.",
    "A whisper calls you from afar, tempting you to come closer.",
    "The ground trembles slightly. Something moves beneath.",
    "A mysterious figure flashes in the distance, then vanishes."
};

static const vector<string> restFlavor = {
    "You find a quiet corner to rest.",
    "The warmth of the campfire makes you feel safe.",
    "You close your eyes, take a deep breath, and recover some strength.",
    "The distant wind sounds like a lullaby. You take a short nap.",
    "You sit on a rock and relax your tense nerves."
};
/**
 * @brief Displays a random flavor text based on the given node type.
 *        The flavor text is printed to the console with decorative asterisks.
 * @param type The type of node (FIGHT, ELITE, BOSS, EVENT, REST). Determines which flavor pool to use.
 * @return void
 */
void showFlavorText(NodeType type) {
    string text;
    switch (type) {
    case FIGHT:
        if (!fightFlavor.empty())
            text = fightFlavor[rand() % fightFlavor.size()];
        break;
    case ELITE:
        if (!eliteFlavor.empty())
            text = eliteFlavor[rand() % eliteFlavor.size()];
        break;
    case BOSS:
        if (!bossFlavor.empty())
            text = bossFlavor[rand() % bossFlavor.size()];
        break;
    case EVENT:
        if (!eventFlavor.empty())
            text = eventFlavor[rand() % eventFlavor.size()];
        break;
    case REST:
        if (!restFlavor.empty())
            text = restFlavor[rand() % restFlavor.size()];
        break;
    default:
        return;
    }
    if (!text.empty()) {
        cout << "\n* " << text << " *\n\n";
    }
}
