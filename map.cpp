#include "map.h"
#include <string>
using namespace std;

vector<Node> getRoute() {
    vector<Node> route(5);

    route[0].type = FIGHT;
    route[0].enemyId = ENEMY_SLIME;

    route[1].type = EVENT;
    route[1].enemyId = -1;

    route[2].type = ELITE;
    route[2].enemyId = ENEMY_GOBLIN;

    route[3].type = REST;
    route[3].enemyId = -1;

    route[4].type = BOSS;
    route[4].enemyId = ENEMY_GOBLIN_BOSS;

    return route;
}

string nodeTypeToString(NodeType type) {
    switch (type) {
    case FIGHT: return "Normal Fight";
    case EVENT: return "Random Event";
    case ELITE: return "Elite Fight";
    case REST:  return "Rest Site";
    case BOSS:  return "Boss Fight";
    default:    return "Unknown";
    }
}
