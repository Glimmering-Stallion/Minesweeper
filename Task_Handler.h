#ifndef TASK_HANDLER //Header Guard
#define TASK_HANDLER

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cctype>
#include <cstdlib>

#include "Grid.h"

using namespace std;



class Task_Handler {
    public:
        // Function definitions:
        void playGame() {

            setGridParameters();

            bool is_first_selection = 1;

            // Manages player choices:
            int choice = 0;
            do {
                m_Current_Grid.displayGrid();
                choice = gridMenu();

                switch (choice) {
                    case 1:
                        if(revealGridPosition(is_first_selection))
                            return;
                        break;
                    case 2:
                        flagGridPosition();
                        break;
                    case 3: {
                        choice = confirmQuit();
                        if(choice == 1) {
                            break;
                        } else {
                            cout << endl << "Game ended." << endl;
                            return;
                        }
                    }
                }

            } while (choice != 3);

        }



        int gridMenu() {
            int choice = 0;

            cout << "1) Reveal a grid position." << endl;
            cout << "2) Flag a grid position." << endl;
            cout << "3) End game." << endl;

            cout << endl << "Select an option: ";
            cin >> choice;
            cout << endl;

            while (cin.fail() || (choice < 1 || choice > 3)) {
                cout << "Please enter a valid choice: ";
                cin.clear();
                cin.ignore(256, '\n');
                cin >> choice;
                cout << endl;
            }

            return choice;
        }



        int confirmQuit() {

            int choice = 0;

            cout << "1) Cancel." << endl;
            cout << "2) Confirm." << endl;
            cout << endl;

            cout << "Select an option: ";
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



        bool victoryStatus() {

            int num_unarmed_cells = (m_Current_Grid.m_grid_height * m_Current_Grid.m_grid_width) - m_Current_Grid.m_num_mines;
            int num_revealed_cells = 0;

            // Count number of revealed grid cells:
            for(int i = 0; i < m_Current_Grid.m_grid_height; i++) {
                for(int j = 0; j < m_Current_Grid.m_grid_width; j++) {
                    if(get<1>(m_Current_Grid.m_grid[i][j]))
                        num_revealed_cells++;
                }
            }

            // cout << "Number of revealed grid cells: " << num_revealed_cells << endl;
            // cout << "Number of unarmed grid cells: " << num_unarmed_cells << endl;
            // cout << endl;

            if(num_revealed_cells == num_unarmed_cells)
                return 1;

            return 0;
        }



        bool revealGridPosition(bool &first_selection) {

            int grid_position_x;
            int grid_position_y;

            bool is_game_end = 0;

            do {

                // m_Current_Grid.displayGrid();

                cout << "- Select a grid position to reveal." << endl;
                cout << "- The origin is at the top-left of the grid." << endl;
                cout << "- Enter 0 to cancel process." << endl;
                cout << endl;

                // Check if game has been won:
                if(victoryStatus()) {
                    cout << "Congratulations, all mines revealed!" << endl;
                    return 1;
                }

                cout << "Enter in x position: ";
                cin >> grid_position_x;
                cout << endl;
                if( (grid_position_x == 0))
                    return 0;

                while (cin.fail() || (grid_position_x < 0 || grid_position_x > m_Current_Grid.m_grid_width)) {
                    cout << "Please enter a valid position." << endl;
                    cout << endl;
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Enter in x position: ";
                    cin >> grid_position_x;
                    if( (grid_position_x == 0))
                        return 0;
                    cout << endl;
                }

                cout << "Enter in y position: ";
                cin >> grid_position_y;
                cout << endl;
                if( (grid_position_y == 0))
                    return 0;
                
                while (cin.fail() || (grid_position_y < 0 || grid_position_y > m_Current_Grid.m_grid_height)) {
                    cout << "Please enter a valid position." << endl;
                    cout << endl;
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Enter in y position: ";
                    cin >> grid_position_y;
                    if( (grid_position_x == 0))
                        return 0;
                    cout << endl;
                }

                // Checks whether the selected grid cell is flagged or not:
                if(get<0>(m_Current_Grid.m_grid[grid_position_y - 1][grid_position_x - 1])) {
                    m_Current_Grid.displayGrid();
                    cout << "Unable to reveal flagged grid cell." << endl;
                    cout << endl;

                // Checks whether the selected grid cell is already revealed or not:
                } else if(get<1>(m_Current_Grid.m_grid[grid_position_y - 1][grid_position_x - 1])) {
                    m_Current_Grid.displayGrid();
                    cout << "Selected grid cell already revealed." << endl;
                    cout << endl;

                // Checks whether the selected grid cell is armed or not:
                } else if((get<2>(m_Current_Grid.m_grid[grid_position_y - 1][grid_position_x - 1])) ) {

                    // Checks whether the current selection is the first selection or not (makes sure that the first selection is not a game-ending scenario):
                    if(first_selection) {

                        first_selection = 0;
                        
                        m_Current_Grid.placeMines(1); // Place mine in another location on the grid
                        get<2>(m_Current_Grid.m_grid[grid_position_y - 1][grid_position_x - 1]) = 0; // Remove mine from current location

                        m_Current_Grid.calculateAdjacentMines(); // Update the data of adjacent mines based on new mine locations
                        m_Current_Grid.floodFill(grid_position_x - 1, grid_position_y - 1); // Perform floodFill at current location
                        m_Current_Grid.displayGrid();

                    } else {

                        get<1>(m_Current_Grid.m_grid[grid_position_y - 1][grid_position_x - 1]) = 1;
                        m_Current_Grid.displayGrid();

                        m_Current_Grid.displayExposedGrid();
                        cout << "Game over!" << endl;

                        is_game_end = 1;
                        return is_game_end;

                    }

                } else {
                    first_selection = 0;
                    m_Current_Grid.floodFill(grid_position_x - 1, grid_position_y - 1);
                    m_Current_Grid.displayGrid();
                }

            } while((grid_position_x != 0) || (grid_position_y != 0));

            return 0;

        }



        void flagGridPosition() {

            int grid_position_x;
            int grid_position_y;

            do {

                // m_Current_Grid.displayGrid();

                cout << "- Select a grid position to flag/unflag." << endl;
                cout << "- The origin is at the top-left of the grid." << endl;
                cout << "- Enter 0 to cancel process." << endl;
                cout << endl;

                cout << "Enter in x position: ";
                cin >> grid_position_x;
                cout << endl;
                if( (grid_position_x == 0))
                    return;

                while (cin.fail() || (grid_position_x < 0 || grid_position_x > m_Current_Grid.m_grid_width)) {
                    cout << "Please enter a valid position." << endl;
                    cout << endl;
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Enter in x position: ";
                    cin >> grid_position_x;
                    if( (grid_position_x == 0))
                        return;
                    cout << endl;
                }

                cout << "Enter in y position: ";
                cin >> grid_position_y;
                cout << endl;
                if( (grid_position_y == 0))
                    return;
                
                while (cin.fail() || (grid_position_y < 0 || grid_position_y > m_Current_Grid.m_grid_height)) {
                    cout << "Please enter a valid position." << endl;
                    cout << endl;
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Enter in y position: ";
                    cin >> grid_position_y;
                    if( (grid_position_x == 0))
                        return;
                    cout << endl;
                }


                // Checks whether the selected grid cell is already revealed or not:
                if(!get<1>(m_Current_Grid.m_grid[grid_position_y - 1][grid_position_x - 1])) {
                    // Toggles the flag for the selected grid cell on or off:
                    if(get<0>(m_Current_Grid.m_grid[grid_position_y - 1][grid_position_x - 1])) { // If there is a flag, remove flag
                        get<0>(m_Current_Grid.m_grid[grid_position_y - 1][grid_position_x - 1]) = 0;
                        m_Current_Grid.displayGrid();
                    } else { // Else, place flag
                        get<0>(m_Current_Grid.m_grid[grid_position_y - 1][grid_position_x - 1]) = 1;
                        m_Current_Grid.displayGrid();
                    }
                } else {
                    m_Current_Grid.displayGrid();
                    cout << "Unable to flag an already revealed grid cell." << endl;
                    cout << endl;
                }
            
            } while((grid_position_x != 0) || (grid_position_y != 0));

        }



        void setGridParameters() {
            int grid_height;
            int grid_width;
            int num_mines;

            cout << "Enter in the dimensions of the grid (height and width within 3-50 cells)." << endl << endl;

            cout << "Height: ";
            cin >> grid_height;
            while (cin.fail() || (grid_height < 3 || grid_height > 50)) {
                cout << endl;
                cout << "Please enter a valid dimension (height within 3-50 cells)." << endl;
                cout << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Height: ";
                cin >> grid_height;
            }


            cout << "Width: ";
            cin >> grid_width;
            while (cin.fail() || (grid_width < 3 || grid_width > 50)) {
                cout << endl;
                cout << "Please enter a valid dimension (width within 3-50 cells)." << endl;
                cout << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Width: ";
                cin >> grid_width;
            }

            cout << "Enter in the number of mines: ";
            cin >> num_mines;
            cout << endl;

            m_Current_Grid.initializeGrid(grid_height, grid_width, num_mines);
        }



    private:
        Grid m_Current_Grid;
};


#endif