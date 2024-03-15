/*
mazeio.cpp
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a
 *  2D dynamically  allocated array.
 *
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem,
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols)
{
    // *** You complete **** CHECKPOINT 1
    
    // call the file using ifstream, named ifile (like in lectures)
    ifstream ifile(filename);
    // actually grab the columns and rows and use them as inputs

    ifile >> *rows;
    ifile >> *cols;
    // if the ifile doesn't exist or we can't use the two numbers
    // then we return NULL 
    if (ifile.fail()) {
      return NULL;
    }
    // a new 2D array for the maze
    char** maze = new char* [*rows];
    for (int i = 0; i < *rows; i++) {
      maze[i] = new char[*cols];
    }
    // fill in the inputs from file and fill it into the 
    // dimensions that we dynamically allocated
    for (int i = 0; i < *rows; i++) {
      for (int j = 0; j < *cols; j++) {
        ifile >> maze[i][j];
      }
    }
    // we want to close the file once we are finished using it
    ifile.close();
    // we want to 
    return maze;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols) {
    // *** You complete **** CHECKPOINT 1
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        cout << maze[i][j];
      }
      cout << endl;
    }
}

