#ifndef UTILS_H
#define UTILS_H

#include <string>

void clearScreen();
void waitForEnter();
int getIntInput(int minVal, int maxVal, const std::string& prompt);
std::string toLower(const std::string& str);

#endif
