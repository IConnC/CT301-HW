#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// George Krier
// gkrier

// NOTE: Suggested Functions

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

bool IsAdjacent() {
    return false;
}

int main(int argc, char* argv[])
{
    if (argc < 2){
        cerr << argv[0] << " Usage:\n" << argv[0] << " filename\n\n" << "The filename passed should contain the following, the integer width of the table, the number of generations then a Width by Width table of characters for setting up the game\n" << endl;
        return -1;
    }
    string filename = argv[1];
    ifstream file_in(filename);
    string line;
    int width;
    int generations;
    file_in >> width >> generations;
    string game_table_alpha(width*width, ' ');
    string game_table_beta(width*width, ' ');
    getline(file_in, line);
    for (int row = 0; file_in && row < width; ++row){
        getline(file_in, line);
        for (int col = 0; col < width; ++col)
        {
            game_table_alpha[col+(row*width)] = line[col];
        }
    }
    // NOTE: Your Code Starts Here
}