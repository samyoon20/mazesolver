/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// Add other prototypes here for any functions you wish to use

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
    int rows, cols, result;
    char** mymaze=NULL;
    const char* invalid_char_message = "Error, invalid character.";
    const char* invalid_maze_message = "Invalid maze.";
    const char* no_path_message = "No path could be found!";

    if(argc < 2)
    {
        cout << "Please provide a maze input file" << endl;
        return 1;
    }
    mymaze = read_maze(argv[1], &rows, &cols); // <---TASK: COMPLETE THIS FOR CHECKPOINT 1

    // For checkpoint 2 you should check the validity of the maze
    // You may do so anywhere you please and can abstract that
    // operation with a function or however you like.

    //================================
    // When working on Checkpoint 4, you will need to call maze_search
    // and output the appropriate message or, if successful, print
    // the maze.  But for Checkpoint 1, we print the maze, regardless.
    
    //print_maze(mymaze, rows, cols);

    bool isInvalid = false;
    // check if the maze itself is invalid
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (mymaze[i][j] != 'S' && mymaze[i][j] != 'F'
        && mymaze[i][j] != '#' && mymaze[i][j] != '.') {
        isInvalid = true;
        break;
        }
      }
    }
    // if the maze is invalid because of invalid characters
    if (isInvalid == true) {
      cout << invalid_char_message;
    }
    result = maze_search(mymaze, rows, cols);
    // if the result in the main function is -1, output invalid maze
    if (result == -1) {
      cout << invalid_maze_message;
    }
    // if the result is 1, that means everything is good!
    else if (result == 1) {
      cout << rows <<  " " << cols << endl;
      print_maze(mymaze, rows, cols);
    }
    // no path if the result is 0 in the main function
    else if (result == 0) {
      cout << no_path_message;
    }

    //================================
    // ADD CODE BELOW 
    // to delete all memory that read_maze allocated: CHECKPOINT 2
    // deallocating memory from the mymaze function earlier
    for (int i = 0; i < rows; i++) {
      delete [] mymaze[i];
    }
    delete [] mymaze;
  return 0;
}
/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols) {
    // *** You complete **** CHECKPOINT 4
    // initialize the starting location
    
    // dynamically allocate predecessor array
    Location** predecessor = new Location* [rows];
    // we use a for loop to create the 2d array
    for (int i = 0; i < rows; i++) {
      predecessor[i] = new Location [cols];
    }
    // explored is a boolean and we also dynamically allocate it
    bool** explored = new bool* [rows];
    // it's a for loop to create the 2d array for it too
    for (int i = 0; i < rows; i++) {
      explored[i] = new bool [cols];
    }
    // a nested loop that sets the explored 2d array to false
    for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
        explored[i][j] = false;
      }
    }
    // initialize the start location
    Location loc_start;
    int s_count = 0;
    int f_count = 0;
    // for loop that counts how many times we see 'S' in the maze
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (maze[i][j] == 'S') {
          s_count++;
          // location start is set to the row and col spot where S is
          loc_start.row = i;
          loc_start.col = j;
          explored[i][j] = true;
        }
        // same idea above, but how many times does 'F' show?
        if (maze[i][j] == 'F') {
          f_count++;
        }
      }
    }
    // if there are more than one 'S' or 'F' or if there are NONE for both
    // then return the invalid maze
    // we also want to deallocate the explored and predecessor arrays  
    if ((s_count > 1 || f_count > 1) || s_count == 0 || f_count == 0) {
      for (int i = 0; i < rows; i++) {
        delete [] explored[i];
        delete [] predecessor[i];
      }
      delete [] explored;
      delete [] predecessor;
      return -1;
    }
    // queue is in the size of the whole maze
    Queue q1(rows*cols);
    // initialize a boolean that will tell us if the maze is finished (set to false)
    bool isFinished = false;
    // initialzie the location where the spot is finished
    Location finish_spot;
    // the start should be added to back in the queue
    q1.add_to_back(loc_start);
    Location location;

    // while the queue is not empty
    // the while and if statements checks for Finish at NORTH
    while (!q1.is_empty()) {
      location = q1.remove_from_front();
      if (location.row - 1 >= 0 && location.col >= 0
      && location.row - 1 < rows && location.col < cols
      && maze[location.row-1][location.col] != '#') {
        if (maze[location.row - 1][location.col] == 'F') {
            isFinished = true;
            finish_spot.row = location.row;
            finish_spot.col = location.col;
            break;
        }
        if (explored[location.row - 1][location.col] == false) {
          explored[location.row - 1][location.col] = true;
          Location new_loc;
          new_loc.row = location.row - 1;
          new_loc.col = location.col;
          q1.add_to_back(new_loc);
          predecessor[location.row - 1][location.col] = location;
        }
      }
      // this checks for Finish to the West
      if (location.row >= 0 && location.col - 1 >= 0
      && location.row < rows && location.col - 1 < cols
      && maze[location.row][location.col-1] != '#') {
        if (maze[location.row][location.col - 1] == 'F') {
            isFinished = true;
            finish_spot.row = location.row;
            finish_spot.col = location.col;
            break;
      }
        if (explored[location.row][location.col - 1] == false) {
          explored[location.row][location.col - 1] = true;
          Location new_loc;
          new_loc.row = location.row;
          new_loc.col = location.col - 1;
          q1.add_to_back(new_loc);
          predecessor[location.row][location.col - 1] = location;
        }
      }
      // Checks for a finish from the SOUTH
      if (location.row >= 0 && location.col >= 0
      && location.row + 1 < rows && location.col < cols
      && maze[location.row + 1][location.col] != '#') {
        if (maze[location.row + 1][location.col] == 'F') {
            isFinished = true;
            finish_spot.row = location.row;
            finish_spot.col = location.col;
            break;
      }
        if (explored[location.row + 1][location.col] == false) {
          explored[location.row + 1][location.col] = true;
          Location new_loc;
          new_loc.row = location.row + 1;
          new_loc.col = location.col;
          q1.add_to_back(new_loc);
          predecessor[location.row + 1][location.col] = location;
        }
      }
      // Checks for the finish on the EAST
      if (location.row >= 0 && location.col >= 0
      && location.row < rows && location.col + 1 < cols
      && maze[location.row][location.col + 1] != '#') {
        if (maze[location.row][location.col + 1] == 'F') {
            isFinished = true;
            finish_spot.row = location.row;
            finish_spot.col = location.col;
            break;
      }
        if (explored[location.row][location.col + 1] == false) {
          explored[location.row][location.col + 1] = true;
          Location new_loc;
          new_loc.row = location.row;
          new_loc.col = location.col + 1;
          q1.add_to_back(new_loc);
          predecessor[location.row][location.col + 1] = location;
        }
      }
    }
    // if the maze is finished then we want to fill the way we went, with astrixs
    if (isFinished == true){
      while (maze[finish_spot.row][finish_spot.col] != 'S') {
        maze[finish_spot.row][finish_spot.col] = '*';
        finish_spot = predecessor[finish_spot.row][finish_spot.col];
      }
      // delete, deallocate the new arrays we created for the exploreds and predecessors arrays
      for (int i = 0; i < rows; i++) {
        delete [] explored[i];
        delete [] predecessor[i];
      }
      delete [] explored;
      delete [] predecessor;

      return 1;
    }
    // we don't need a nested for loop because it saves space to just double whammy the delete functions
    else {
      for (int i = 0; i < rows; i++) {
        delete [] explored[i];
        delete [] predecessor[i];
      }
      delete [] explored;
      delete [] predecessor;

    return 0;
    }
}

