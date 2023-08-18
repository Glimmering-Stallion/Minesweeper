#ifndef GRID //Header Guard
#define GRID

#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
#include<tuple> 

using namespace std;

// Grid Cell symbols:
const string Unrevealed_Grid_Cell = "■";
const string Empty_Grid_Cell = "□";
const string Numbered_Grid_Cell_1 = "➀";
const string Numbered_Grid_Cell_2 = "➁";
const string Numbered_Grid_Cell_3 = "➂";
const string Numbered_Grid_Cell_4 = "➃";
const string Numbered_Grid_Cell_5 = "➄";
const string Numbered_Grid_Cell_6 = "➅";
const string Numbered_Grid_Cell_7 = "➆";
const string Numbered_Grid_Cell_8 = "➇";
const string Armed_Grid_Cell = "❁";
const string Flagged_Grid_Cell = "⛝";

// Grid coordinate symbols:
const string Coordinate_Number_1 = "①";
const string Coordinate_Number_2 = "②";
const string Coordinate_Number_3 = "③";
const string Coordinate_Number_4 = "④";
const string Coordinate_Number_5 = "⑤";
const string Coordinate_Number_6 = "⑥";
const string Coordinate_Number_7 = "⑦";
const string Coordinate_Number_8 = "⑧";
const string Coordinate_Number_9 = "⑨";
const string Coordinate_Number_10 = "⑩";
const string Coordinate_Number_11 = "⑪";
const string Coordinate_Number_12 = "⑫";
const string Coordinate_Number_13 = "⑬";
const string Coordinate_Number_14 = "⑭";
const string Coordinate_Number_15 = "⑮";
const string Coordinate_Number_16 = "⑯";
const string Coordinate_Number_17 = "⑰";
const string Coordinate_Number_18 = "⑱";
const string Coordinate_Number_19 = "⑲";
const string Coordinate_Number_20 = "⑳";
const string Coordinate_Number_21 = "㉑";
const string Coordinate_Number_22 = "㉒";
const string Coordinate_Number_23 = "㉓";
const string Coordinate_Number_24 = "㉔";
const string Coordinate_Number_25 = "㉕";
const string Coordinate_Number_26 = "㉖";
const string Coordinate_Number_27 = "㉗";
const string Coordinate_Number_28 = "㉘";
const string Coordinate_Number_29 = "㉙";
const string Coordinate_Number_30 = "㉚";
const string Coordinate_Number_31 = "㉛";
const string Coordinate_Number_32 = "㉜";
const string Coordinate_Number_33 = "㉝";
const string Coordinate_Number_34 = "㉞";
const string Coordinate_Number_35 = "㉟";
const string Coordinate_Number_36 = "㊱";
const string Coordinate_Number_37 = "㊲";
const string Coordinate_Number_38 = "㊳";
const string Coordinate_Number_39 = "㊴";
const string Coordinate_Number_40 = "㊵";
const string Coordinate_Number_41 = "㊶";
const string Coordinate_Number_42 = "㊷";
const string Coordinate_Number_43 = "㊸";
const string Coordinate_Number_44 = "㊹";
const string Coordinate_Number_45 = "㊺";
const string Coordinate_Number_46 = "㊻";
const string Coordinate_Number_47 = "㊼";
const string Coordinate_Number_48 = "㊽";
const string Coordinate_Number_49 = "㊾";
const string Coordinate_Number_50 = "㊿";



struct Grid {
  //Default constructor
  Grid(){}



  // Overloaded constructor:
  Grid(int grid_height, int grid_width, int num_mines){
    m_grid_height = grid_height;
    m_grid_width = grid_width;
    m_num_mines = num_mines;
  }


  // Destructor:
  ~Grid() {}



  // Initialize the grid:
  void initializeGrid(int grid_height, int grid_width, int num_mines) {
    m_grid_height = grid_height;
    m_grid_width = grid_width;
    m_num_mines = num_mines;

    m_is_revealed = 0;
    m_is_armed = 0;
    m_is_flagged = 0;
    m_num_adjacent_mines = 0;

    vector< tuple<bool, bool, bool, int> > m_grid_row(grid_width,  {m_is_flagged, m_is_revealed, m_is_armed, m_num_adjacent_mines});

    for(int i = 0; i < grid_height; i++) {
      m_grid.push_back(m_grid_row);
    }

    placeMines(m_num_mines);
    calculateAdjacentMines();
  }



  // Place mines in random locations on the board:
  void placeMines(int num_mines) {
    int counter = 0;
    srand(time(NULL));
    while (counter < num_mines) {
      int x = rand() % m_grid_width;
      int y = rand() % m_grid_height;

      // Check whether the current location is armed or not (prevents arming the same location multiple times):
      if(!get<2>(m_grid[y][x])) {
        get<2>(m_grid[y][x]) = 1; // Arm random location with mine
        counter++;
      }
    }

    // cout << "Mines placed." << endl; // Debugging
  }



  // Calculate the number of mines surrounding each cell:
  void calculateAdjacentMines() {
    for (int i = 0; i < m_grid_height; i++) {
      for (int j = 0; j < m_grid_width; j++) {
        if(get<2>(m_grid[i][j])) {
          continue;
        }

        // Mine counter for number of mines in proximity:
        int count = 0;
        // Scan through a three by three area on the grid:
        for (int y = i - 1; y <= i + 1; y++) {
          for (int x = j - 1; x <= j + 1; x++) {
            // Check if search area is within the confines of the grid:
            if ( (y >= 0 && y < m_grid_height) && (x >= 0 && x < m_grid_width) ) {
              // Check if there is a mine present in the seach area:
              if (get<2>(m_grid[y][x]))
                count++;
            }
          }
        }

        get<3>(m_grid[i][j]) = count;
      }
    }
  }



  // Recursively reveals a grid cell if empty end all adjacent empty grid cells:
  void floodFill(int x, int y) { 
    // Base cases:
    if ( (x < 0 || x >= m_grid_width) || (y < 0 || y >= m_grid_height) ) // Checks whether the given x and y values are within the confines of the grid or not
      return;
    if (get<1>(m_grid[y][x])) // Checks whether the current grid cell is already revealed or not
      return;
    if (get<0>(m_grid[y][x])) // Checks whether the current grid cell is flagged or not
      return;
    if (get<2>(m_grid[y][x])) // Checks whether the current grid cell is armed or not
      return;
  
    // Checks whether the current grid cell's neighbor is armed or not
    if(get<3>(m_grid[y][x]) > 0) {
      get<1>(m_grid[y][x]) = 1; // Change the current grid cell from unrevealed to revealed
      return;
    }

    get<1>(m_grid[y][x]) = 1; // Change the current grid cell from unrevealed to revealed
  
    // Recursively call for east, west, north and south of current grid cell:
    floodFill(x + 1, y);
    floodFill(x - 1, y);
    floodFill(x, y + 1);
    floodFill(x, y - 1);
  }



  // Displays the grid with the use of various alt-code symbols as the grid cells:
  void displayGrid() {

    // Display the grid without coordinate numbers:
    // for(int i = 0; i < (m_grid_height); i++) {
    //     for(int j = 0; j < (m_grid_width); j++) {
    //         displayGridCellType(i, j);
    //     }
    //     cout << endl;
    // }
    // cout << endl;


    // Display the grid with coordinate numbers:
    for(int i = -1; i < (m_grid_height); i++) {
        for(int j = -1; j < (m_grid_width); j++) {
            if(j == -1) {
                if((i == -1) && (j == -1))
                    cout << setw(2) << " ";
                else {
                  if(i < 21) {
                    if(i == 0) {
                      cout << Coordinate_Number_1 << setw(1) << "";
                    } else if(i == 1) {
                      cout << Coordinate_Number_2 << setw(1) << "";
                    } else if(i == 2) {
                      cout << Coordinate_Number_3 << setw(1) << "";
                    } else if(i == 3) {
                      cout << Coordinate_Number_4 << setw(1) << "";
                    } else if(i == 4) {
                      cout << Coordinate_Number_5 << setw(1) << "";
                    } else if(i == 5) {
                      cout << Coordinate_Number_6 << setw(1) << "";
                    } else if(i == 6) {
                      cout << Coordinate_Number_7 << setw(1) << "";
                    } else if(i == 7) {
                      cout << Coordinate_Number_8 << setw(1) << "";
                    } else if(i == 8) {
                      cout << Coordinate_Number_9 << setw(1) << "";
                    } else if(i == 9) {
                      cout << Coordinate_Number_10 << setw(1) << "";
                    } else if(i == 10) {
                      cout << Coordinate_Number_11 << setw(1) << "";
                    } else if(i == 11) {
                      cout << Coordinate_Number_12 << setw(1) << "";
                    } else if(i == 12) {
                      cout << Coordinate_Number_13 << setw(1) << "";
                    } else if(i == 13) {
                      cout << Coordinate_Number_14 << setw(1) << "";
                    } else if(i == 14) {
                      cout << Coordinate_Number_15 << setw(1) << "";
                    } else if(i == 15) {
                      cout << Coordinate_Number_16 << setw(1) << "";
                    } else if(i == 16) {
                      cout << Coordinate_Number_17 << setw(1) << "";
                    } else if(i == 17) {
                      cout << Coordinate_Number_18 << setw(1) << "";
                    } else if(i == 18) {
                      cout << Coordinate_Number_19 << setw(1) << "";
                    } else if(i == 19) {
                      cout << Coordinate_Number_20 << setw(1) << "";
                    } else if(i == 20) {
                      cout << Coordinate_Number_21 << setw(0) << "";
                    }
                  } else {
                    if(i == 20) {
                      cout << Coordinate_Number_21 << setw(0) << "";
                    } else if(i == 21) {
                      cout << Coordinate_Number_22 << setw(0) << "";
                    } else if(i == 22) {
                      cout << Coordinate_Number_23 << setw(0) << "";
                    } else if(i == 23) {
                      cout << Coordinate_Number_24 << setw(0) << "";
                    } else if(i == 24) {
                      cout << Coordinate_Number_25 << setw(0) << "";
                    } else if(i == 25) {
                      cout << Coordinate_Number_26 << setw(0) << "";
                    } else if(i == 26) {
                      cout << Coordinate_Number_27 << setw(0) << "";
                    } else if(i == 27) {
                      cout << Coordinate_Number_28 << setw(0) << "";
                    } else if(i == 28) {
                      cout << Coordinate_Number_29 << setw(0) << "";
                    } else if(i == 29) {
                      cout << Coordinate_Number_30 << setw(0) << "";
                    } else if(i == 30) {
                      cout << Coordinate_Number_31 << setw(0) << "";
                    } else if(i == 31) {
                      cout << Coordinate_Number_32 << setw(0) << "";
                    } else if(i == 32) {
                      cout << Coordinate_Number_33 << setw(0) << "";
                    } else if(i == 33) {
                      cout << Coordinate_Number_34 << setw(0) << "";
                    } else if(i == 34) {
                      cout << Coordinate_Number_35 << setw(0) << "";
                    } else if(i == 35) {
                      cout << Coordinate_Number_36 << setw(0) << "";
                    } else if(i == 36) {
                      cout << Coordinate_Number_37 << setw(0) << "";
                    } else if(i == 37) {
                      cout << Coordinate_Number_38 << setw(0) << "";
                    } else if(i == 38) {
                      cout << Coordinate_Number_39 << setw(0) << "";
                    } else if(i == 39) {
                      cout << Coordinate_Number_40 << setw(0) << "";
                    } else if(i == 40) {
                      cout << Coordinate_Number_41 << setw(0) << "";
                    } else if(i == 41) {
                      cout << Coordinate_Number_42 << setw(0) << "";
                    } else if(i == 42) {
                      cout << Coordinate_Number_43 << setw(0) << "";
                    } else if(i == 43) {
                      cout << Coordinate_Number_44 << setw(0) << "";
                    } else if(i == 44) {
                      cout << Coordinate_Number_45 << setw(0) << "";
                    } else if(i == 45) {
                      cout << Coordinate_Number_46 << setw(0) << "";
                    } else if(i == 46) {
                      cout << Coordinate_Number_47 << setw(0) << "";
                    } else if(i == 47) {
                      cout << Coordinate_Number_48 << setw(0) << "";
                    } else if(i == 48) {
                      cout << Coordinate_Number_49 << setw(0) << "";
                    } else if(i == 49) {
                      cout << Coordinate_Number_50 << setw(0) << "";
                    }
                  }
                }
                
            } else if (i == -1) {
              if(j == 0) {
                cout << setw(4) << Coordinate_Number_1;
              } else if(j == 1) {
                cout << setw(4) << Coordinate_Number_2;
              } else if(j == 2) {
                cout << setw(4) << Coordinate_Number_3;
              } else if(j == 3) {
                cout << setw(4) << Coordinate_Number_4;
              } else if(j == 4) {
                cout << setw(4) << Coordinate_Number_5;
              } else if(j == 5) {
                cout << setw(4) << Coordinate_Number_6;
              } else if(j == 6) {
                cout << setw(4) << Coordinate_Number_7;
              } else if(j == 7) {
                cout << setw(4) << Coordinate_Number_8;
              } else if(j == 8) {
                cout << setw(4) << Coordinate_Number_9;
              } else if(j == 9) {
                cout << setw(4) << Coordinate_Number_10;
              } else if(j == 10) {
                cout << setw(4) << Coordinate_Number_11;
              } else if(j == 11) {
                cout << setw(4) << Coordinate_Number_12;
              } else if(j == 12) {
                cout << setw(4) << Coordinate_Number_13;
              } else if(j == 13) {
                cout << setw(4) << Coordinate_Number_14;
              } else if(j == 14) {
                cout << setw(4) << Coordinate_Number_15;
              } else if(j == 15) {
                cout << setw(4) << Coordinate_Number_16;
              } else if(j == 16) {
                cout << setw(4) << Coordinate_Number_17;
              } else if(j == 17) {
                cout << setw(4) << Coordinate_Number_18;
              } else if(j == 18) {
                cout << setw(4) << Coordinate_Number_19;
              } else if(j == 19) {
                cout << setw(4) << Coordinate_Number_20;
              } else if(j == 20) {
                cout << setw(4) << Coordinate_Number_21;
              } else if(j == 21) {
                cout << setw(3) << Coordinate_Number_22;
              } else if(j == 22) {
                cout << setw(3) << Coordinate_Number_23;
              } else if(j == 23) {
                cout << setw(3) << Coordinate_Number_24;
              } else if(j == 24) {
                cout << setw(3) << Coordinate_Number_25;
              } else if(j == 25) {
                cout << setw(3) << Coordinate_Number_26;
              } else if(j == 26) {
                cout << setw(3) << Coordinate_Number_27;
              } else if(j == 27) {
                cout << setw(3) << Coordinate_Number_28;
              } else if(j == 28) {
                cout << setw(3) << Coordinate_Number_29;
              } else if(j == 29) {
                cout << setw(3) << Coordinate_Number_30;
              } else if(j == 30) {
                cout << setw(3) << Coordinate_Number_31;
              } else if(j == 31) {
                cout << setw(3) << Coordinate_Number_32;
              } else if(j == 32) {
                cout << setw(3) << Coordinate_Number_33;
              } else if(j == 33) {
                cout << setw(3) << Coordinate_Number_34;
              } else if(j == 34) {
                cout << setw(3) << Coordinate_Number_35;
              } else if(j == 35) {
                cout << setw(3) << Coordinate_Number_36;
              } else if(j == 36) {
                cout << setw(3) << Coordinate_Number_37;
              } else if(j == 37) {
                cout << setw(3) << Coordinate_Number_38;
              } else if(j == 38) {
                cout << setw(3) << Coordinate_Number_39;
              } else if(j == 39) {
                cout << setw(3) << Coordinate_Number_40;
              } else if(j == 40) {
                cout << setw(3) << Coordinate_Number_41;
              } else if(j == 41) {
                cout << setw(3) << Coordinate_Number_42;
              } else if(j == 42) {
                cout << setw(3) << Coordinate_Number_43;
              } else if(j == 43) {
                cout << setw(3) << Coordinate_Number_44;
              } else if(j == 44) {
                cout << setw(3) << Coordinate_Number_45;
              } else if(j == 45) {
                cout << setw(3) << Coordinate_Number_46;
              } else if(j == 46) {
                cout << setw(3) << Coordinate_Number_47;
              } else if(j == 47) {
                cout << setw(3) << Coordinate_Number_48;
              } else if(j == 48) {
                cout << setw(3) << Coordinate_Number_49;
              } else if(j == 49) {
                cout << setw(3) << Coordinate_Number_50;
              }
            } else
              displayGridCellType(i, j);
        }
        cout << endl;
    }
    cout << endl;

  }



  // Displays the grid with the use of various alt-code symbols as the grid cells:
  void displayExposedGrid() {

    // Diplays the data of all cells (for debugging purposes):
    // for(int i = 0; i < (m_Current_Grid.m_grid_height ); i++) {
    //     for(int j = 0; j < (m_Current_Grid.m_grid_width ); j++) {
    //         cout << "{";
    //         cout << get<0>(m_Current_Grid.m_grid[i][j]);
    //         cout << get<1>(m_Current_Grid.m_grid[i][j]);
    //         cout << get<2>(m_Current_Grid.m_grid[i][j]);
    //         cout << get<3>(m_Current_Grid.m_grid[i][j]);
    //         cout << "} ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;


    // Display the grid without hidden grid cells:
    for(int i = 0; i < (m_grid_height ); i++) {
      for(int j = 0; j < (m_grid_width ); j++) {
        if (get<2>(m_grid[i][j]) == 1) {
          cout << setw(4) << Armed_Grid_Cell;
        }
        else {
          if(get<3>(m_grid[i][j]) == 1) {
            cout << "" << setw(4) << Numbered_Grid_Cell_1;
          } else if(get<3>(m_grid[i][j]) == 2) {
            cout << setw(4) << Numbered_Grid_Cell_2;
          } else if(get<3>(m_grid[i][j]) == 3) {
            cout << setw(4) << Numbered_Grid_Cell_3;
          } else if(get<3>(m_grid[i][j]) == 4) {
            cout << setw(4) << Numbered_Grid_Cell_4;
          } else if(get<3>(m_grid[i][j]) == 5) {
            cout << setw(4) << Numbered_Grid_Cell_5;
          } else if(get<3>(m_grid[i][j]) == 6) {
            cout << setw(4) << Numbered_Grid_Cell_6;
          } else if(get<3>(m_grid[i][j]) == 7) {
            cout << setw(4) << Numbered_Grid_Cell_7;
          } else if(get<3>(m_grid[i][j]) == 8) {
            cout << setw(4) << Numbered_Grid_Cell_8;
          } else {
            cout << setw(4) << Empty_Grid_Cell;
          }
        }
      }
      cout << endl;
    }
    cout << endl;

  }



  // Determines what type of grid symbol to display from the status of the given grid cell (helper funciton for displayGrid):
  void displayGridCellType(int x, int y) {
    if(get<0>(m_grid[x][y])) {
        cout << setw(4) << Flagged_Grid_Cell;
    } else {
      if(!get<1>(m_grid[x][y])) {
        cout << setw(4) << Unrevealed_Grid_Cell;
      } else {
        if(get<2>(m_grid[x][y])) {
          cout << setw(4) << Armed_Grid_Cell;
        } else {
          if(get<3>(m_grid[x][y]) == 1) {
            cout << setw(4) << Numbered_Grid_Cell_1;
          } else if(get<3>(m_grid[x][y]) == 2) {
            cout << setw(4) << Numbered_Grid_Cell_2;
          } else if(get<3>(m_grid[x][y]) == 3) {
            cout << setw(4) << Numbered_Grid_Cell_3;
          } else if(get<3>(m_grid[x][y]) == 4) {
            cout << setw(4) << Numbered_Grid_Cell_4;
          } else if(get<3>(m_grid[x][y]) == 5) {
            cout << setw(4) << Numbered_Grid_Cell_5;
          } else if(get<3>(m_grid[x][y]) == 6) {
            cout << setw(4) << Numbered_Grid_Cell_6;
          } else if(get<3>(m_grid[x][y]) == 7) {
            cout << setw(4) << Numbered_Grid_Cell_7;
          } else if(get<3>(m_grid[x][y]) == 8) {
            cout << setw(4) << Numbered_Grid_Cell_8;
          } else {
            cout << setw(4) << Empty_Grid_Cell;
          }
        }
      }
    }
  }



  // Member variables:
  int m_grid_height;
  int m_grid_width;
  int m_num_mines;

  bool m_is_flagged;
  bool m_is_revealed;
  bool m_is_armed;
  int m_num_adjacent_mines;

  vector< vector< tuple<bool, bool, bool, int> > > m_grid;
};

#endif