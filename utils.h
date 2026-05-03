#ifndef UTILS_H
#define UTILS_H

#include <string>
/**
 * @brief Clears the terminal screen using ANSI escape sequences.
 * @param none
 * @return void
 */
void clearScreen();
/**
 * @brief Waits for the user to press the Enter key, ignoring any previous input in the buffer.
 * @param none
 * @return void
 */
void waitForEnter();
/**
 * @brief Reads and validates an integer input from the user within a specified range.
 *        Repeats the prompt until a valid integer is entered.
 * @param minVal The minimum acceptable value (inclusive).
 * @param maxVal The maximum acceptable value (inclusive).
 * @param prompt The message displayed to the user before input.
 * @return int A valid integer between minVal and maxVal (inclusive).
 */
int getIntInput(int minVal, int maxVal, const std::string& prompt);
/**
 * @brief Converts all alphabetic characters in a string to lowercase.
 *        Non-alphabetic characters remain unchanged.
 * @param str The input string to be converted.
 * @return std::string A new string with all characters converted to lowercase.
 */
std::string toLower(const std::string& str);

#endif
