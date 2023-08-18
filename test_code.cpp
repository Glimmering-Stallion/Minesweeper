#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <unordered_map>

using namespace std;

const int BOARD_SIZE = 10;
const int NUM_MINES = 10;

std::vector<std::vector<int>> board(BOARD_SIZE, std::vector<int>(BOARD_SIZE));



void initializeBoard() {
    // Place mines randomly on the board
    for (int i = 0; i < NUM_MINES; i++) {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        board[x][y] = -1;
    }

    // Calculate the number of mines surrounding each cell
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == -1) {
                continue;
            }

            int count = 0;
            for (int x = i - 1; x <= i + 1; x++) {
                for (int y = j - 1; y <= j + 1; y++) {
                    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
                        if (board[x][y] == -1) {
                            count++;
                        }
                    }
                }
            }

            board[i][j] = count;
        }
    }
}



void printBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == -1) {
                std::cout << "* ";
            } else {
                std::cout << board[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}



int main() {
    // Random Number Generator:
    srand(time(NULL)); // Seeds random number generator (psuedo)
    // cout << time(NULL) << endl; // Outputs time value
    const int MIN = 0;
    const int MAX = 1;
    const int NUM_ITERATIONS = 10;
    cout << rand() << endl; // Outputs a random number
    for(int i = 0; i < NUM_ITERATIONS; i++){
        cout << rand() % (MAX - MIN + 1) + MIN << endl; // Outputs a set of random numbers within given range
    }

    // Unordered Map:
    unordered_map<string, string> grid_element = {
        {"Grid Cell", "❑"}
    };

    auto print_key_value = [](const auto& key, const auto& value)
    {
        cout << "Key:[" << key << "] Value:[" << value << "]\n";
    };

    for( const auto& [key, value] : grid_element )
        print_key_value(key, value);


    // Tuple:
    tuple <char, int, float> some_tuple; // Declaring a tuple
    some_tuple = make_tuple('a', 10, 15.5); // Assigning values to the tuple using make_tuple()
    cout << get<0>(some_tuple) << " " << get<1>(some_tuple) << " " << get<2>(some_tuple) << endl; // Printing values of the above tuple
    get<0>(some_tuple) = 'b'; // Changing values of the above tuple



    vector< vector<tuple<int, int, int> > > myContainer;

    // Minesweeper Function Tests:
    // initializeBoard();
    // printBoard();


    // Whitespace remover:
    cout << "Dimple" << setw(3);
    cout << "エクボ" << endl;



    return 0;
}