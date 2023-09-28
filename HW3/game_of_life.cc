#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "game_of_life.h"

using namespace std;

// George Krier
// gkrier


/*
OutputGeneration()
Input: 
    A String representing the Generation to output. This should be passed by Reference ex: String &gen
    An Int reprsenting the current Generation Count
    An Int reprsenting the width of the table
Returns: Nothing
Function:
    Prints out "Generation: 0" with a new line and prints out each row of the game table with a newline after each row end.

CalculateGeneration
Input:
    An Integer containing the width of each row
    A String Reference for the "Current" Generation EX: String &curr_gen
    A String Reference for the "Next" Generation EX: String &next_gen
Returns: Nothing
Function:
    For each cell in the table, perform the rules of the game of life on it.
    Count the number of Alive Neighbors and cross check that count with the rules of the Game Of Life
    Then update the cell information in the "next generation" string
*/



game_of_life::game_of_life(std::string filename) {
    game_of_life::live_cell = '*';
    game_of_life::dead_cell = '-';
    
    InitializeFromFile(filename);
}

game_of_life::game_of_life(std::string filename, int pregens) {
    game_of_life::live_cell = '*';
    game_of_life::dead_cell = '-';

    InitializeFromFile(filename);
    NextNGen(pregens);
}
    
game_of_life::game_of_life(std::string filename, char _live_cell, char _dead_cell) {
    live_cell = _live_cell;
    dead_cell = _dead_cell;
    
    InitializeFromFile(filename);
}
        
game_of_life::game_of_life(std::string filename, char _live_cell, char _dead_cell, int pregens) {
    live_cell = _live_cell;
    dead_cell = _dead_cell;
    
    InitializeFromFile(filename);

    NextNGen(pregens);
}

void game_of_life::InitializeFromFile(string filename) {
    ifstream file_in(filename);
    string line;
    file_in >> width >> height;

    generation = string(width * height, dead_cell);
    getline(file_in, line);
    for (int row = 0; file_in && row < height; ++row){
        getline(file_in, line);
        for (int col = 0; col < width; ++col)
        {
            generation[col+(row*width)] = line[col];
        }
    }
}

int game_of_life::GetGenerations() {
    return generation_number;
}

void game_of_life::NextGen() {
    string next_generation(height*width, dead_cell);
    CalculateGeneration(next_generation);
    generation = next_generation;
    generation_number++;
}

void game_of_life::NextNGen(int gens) {
    for (int i=0; i < gens; i++) {
        NextGen();
    }
}

void game_of_life::SetLiveCell(char _live_cell) {
    live_cell = _live_cell;
}

void game_of_life::SetDeadCell(char _dead_cell) {
    dead_cell = _dead_cell;
}

game_of_life& game_of_life::operator+(const int gens) { // Increments by generations
    NextNGen(gens);
    return *this;
}

game_of_life& game_of_life::operator++() { // Pre Increment
    game_of_life::NextGen();
    return *this;
}

game_of_life game_of_life::operator++(const int fake) { // Post Increment
    game_of_life temp = *this;
    game_of_life::NextGen();
    return temp;
}

std::string game_of_life::ToString() const {
    stringstream out("");
    out << "Generation: " << generation << "\n";
    for (int row=0; row < height; row++) {
        for (int col=0; col < width; col++) {
            out << generation[col+(row*width)];
        }
        out << "\n";
    }
    return out.str();
}

std::ostream& operator<<(std::ostream &os, const game_of_life &game) {
    string out = game.ToString();
    for (size_t i=0; i < out.length(); i++) {
        os.put(out[i]);
    }
    return os;
}




// Returns an integer array of all cells that are currently alive
int game_of_life::CountAliveAdjacentCells(int index) {
    int adjacent = 0;

    int curr_index;
    for (int row=(index / height) - 1; row <= (index / height) + 1; row++) {
        for (int col=(index % width) - 1; col <= (index % width) + 1; col++) {
            // Gets current index allowing for out of bound indexes to get wrapped around cells.
            curr_index = ((col + width) % width + (((row + height) % height) * height));

            // If current index continue past the next if statment
            if (curr_index == index) continue;

            if (generation[curr_index] == live_cell) {
                adjacent++;
            }
        }
    }

    return adjacent;
}

// Checks if the current cell should be alive or dead
bool game_of_life::IsCellAlive(int alive_neighbors, bool currently_alive) {

    // A live cell with fewer than two live neighbors dies (underpopulation). (1)
    // A live cell with more than three live neighbors dies (overpopulation). (3)
    if (currently_alive && (alive_neighbors < 2 || alive_neighbors > 3)) return false;

    // A live cell with two or three live neighbors lives on to the next generation. (2)
    else if (currently_alive) return true;

    // A dead cell with exactly three live neighbors it comes to life (rebirth). (4)
    if (!currently_alive && alive_neighbors == 3) return true;

    return false;
}

// Outputs the cells
void OutputGeneration(const string &gen, int generation_number, int width) {
    cout << "Generation: " << generation_number << "\n";
    for (int row=0; row < width; row++) {
        for (int col=0; col < width; col++) {
            cout << gen[col+(row*width)];
        }
        cout << "\n";
    }
}

// Calculates the next cell generation
void game_of_life::CalculateGeneration(string &next_gen) {

    int alive_neighbors = 0;

    for (int row=0; row < height; row++) {
        for (int col=0; col < width; col++) {
            // Gets the number of alive and adjacent cells
            alive_neighbors = CountAliveAdjacentCells(col+(row*width));

            // Sets cells to dead or alive depending on if CalculateIsAlive is true or false
            // Second argument checks to see if current cell is alive or not
            if (IsCellAlive(alive_neighbors, (generation[col+(row*width)] == live_cell))) {
                next_gen[col+(row*width)] = live_cell;
            } else {
                next_gen[col+(row*width)] = dead_cell;
            }
        }
    }
}