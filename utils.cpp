#include "utils.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cstdlib>

using namespace std;
//Clear the current terminal screen 
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}
//Wait for the user to press the Enter key
void waitForEnter() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
//Read the integer input by the user
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
//transform to lowercase
string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
