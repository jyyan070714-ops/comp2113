#include "utils.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cstdlib>

using namespace std;
/**
 * @brief Clears the current terminal screen using ANSI escape sequences.
 * @param none
 * @return void
 */
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}
/**
 * @brief Waits for the user to press the Enter key before continuing.
 *        Ignores any remaining input in the buffer.
 * @param none
 * @return void
 */
void waitForEnter() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
/**
 * @brief Reads an integer input from the user and validates it within a specified range.
 *        Repeats the prompt until a valid integer is entered.
 * @param minVal The minimum acceptable value (inclusive).
 * @param maxVal The maximum acceptable value (inclusive).
 * @param prompt The message displayed to the user before input.
 * @return int A valid integer between minVal and maxVal (inclusive).
 */
int getIntInput(int minVal, int maxVal, const string& prompt) {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer.\n";
        }
        else if (input < minVal || input > maxVal) {
            cout << "Input out of range [" << minVal << ", " << maxVal << "]. Try again.\n";
        }
        else {
            break;
        }
    }
    return input;
}
/**
 * @brief Converts all alphabetic characters in a string to lowercase.
 * @param str The input string to be converted.
 * @return string A new string with all characters converted to lowercase.
 */
string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
