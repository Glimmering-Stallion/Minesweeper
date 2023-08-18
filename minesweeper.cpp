// To compile: g++ -Wall minesweeper.cpp -o minesweeper
// To run: ./minesweeper
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cctype>
#include <cstdlib>

#include "Task_Handler.h"

using namespace std;

// Function declarations:
void runGame();
int mainMenu();



// Function definitions:
void runGame() {

    cout << endl << "Welcome to Minesweeper." << endl;

    // Manages player choices:
    int choice = 0;
    do {
        
        choice = mainMenu();

        switch (choice) {
            case 1: {
                Task_Handler NewGame;
                NewGame.playGame();
                break;
            } case 2:
                cout << "Minesweeper quit." << endl;

        }

    } while (choice != 2);

}



int mainMenu() {
    int choice = 0;

    cout << endl;
    cout << "1) New game." << endl;
    cout << "2) Quit Minesweeper." << endl;

    cout << endl << "Select an option: ";
    cin >> choice;
    cout << endl;

    while (cin.fail() || (choice < 1 || choice > 2)) {
        cout << "Please enter a valid choice: ";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> choice;
        cout << endl;
    }

    return choice;
}



int main () {
    runGame();
    return 0;
}