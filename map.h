#pragma once

#include "common.h"
#include <string>

struct Node {
    NodeType type;
    int enemyId;
};

void getRoute(Node route[], int size);
std::string nodeTypeToString(NodeType type);


