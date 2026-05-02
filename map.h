#pragma once
#include "common.h"
#include <string>
#include <vector>

struct Node {
    NodeType type;
    int enemyId;
};

std::vector<Node> getRoute();
std::string nodeTypeToString(NodeType type);
