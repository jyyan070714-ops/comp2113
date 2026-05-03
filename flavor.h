#ifndef FLAVOR_H
#define FLAVOR_H

#include "common.h"
/**
 * @brief Displays a random flavorful description text based on the given node type.
 *        The text is printed to the console with decorative asterisks.
 * @param type The type of node (FIGHT, ELITE, BOSS, EVENT, REST) to determine which flavor pool to use.
 * @return void
 */
void showFlavorText(NodeType type);

#endif // FLAVOR_H
