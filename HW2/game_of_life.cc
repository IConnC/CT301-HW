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
const static char ALIVE_CHARACTER = '*';
const static char DEAD_CHARACTER = '-';

// Returns an integer array of all cells that are currently alive
int CountLiveAdjacent(int width, const string &curr_gen, int index) {
    int adjacent = 0;


    int curr_index;
    for (int row=(index / width) - 1; row <= (index / width) + 1; row++) {
        for (int col=(index % width) - 1; col <= (index % width) + 1; col++) {
            // Gets current index allowing for out of bound indexes to get wrapped around cells.
            curr_index = ((col + width) % width + (((row + width) % width) * width));

            // If current index continue past the next if statment
            if (curr_index == index) continue;

            if (curr_gen[curr_index] == ALIVE_CHARACTER) {
                adjacent++;
            }
        }
    }

    return adjacent;
}

// Checks if the current cell should be alive or dead
bool CalculateIsAlive(int alive_neighbors, bool currently_alive) {

    // A live cell with fewer than two live neighbors dies (underpopulation). (1)
    // A live cell with more than three live neighbors dies (overpopulation). (3)
    if (currently_alive && (alive_neighbors < 2 || alive_neighbors > 3)) return false;

    // A live cell with two or three live neighbors lives on to the next generation. (2)
    else if (currently_alive) return true;

    // A dead cell with exactly three live neighbors it comes to life (rebirth). (4)
    if (!currently_alive && alive_neighbors == 3) return true;

    //cout << "\n\nSomething very bad happened\n\n";
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
void CalculateGeneration(int width, const string &curr_gen, string &next_gen) {

    int alive_neighbors = 0;

    for (int row=0; row < width; row++) {
        for (int col=0; col < width; col++) {
            // Gets the number of alive and adjacent cells
            alive_neighbors = CountLiveAdjacent(width, curr_gen, col+(row*width));

            // Sets cells to dead or alive depending on if CalculateIsAlive is true or false
            // Second argument checks to see if current cell is alive or not
            if (CalculateIsAlive(alive_neighbors, (curr_gen[col+(row*width)] == ALIVE_CHARACTER))) {
                next_gen[col+(row*width)] = ALIVE_CHARACTER;
            } else {
                next_gen[col+(row*width)] = DEAD_CHARACTER;
            }
        }
    }
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
    string game_table_alpha(width*width, DEAD_CHARACTER);
    string game_table_beta(width*width, DEAD_CHARACTER);
    getline(file_in, line);
    for (int row = 0; file_in && row < width; ++row){
        getline(file_in, line);
        for (int col = 0; col < width; ++col)
        {
            game_table_alpha[col+(row*width)] = line[col];
        }
    }

    for (int gen=0; gen < generations + 1; gen++) {
        OutputGeneration(game_table_alpha, gen, width);
        CalculateGeneration(width, game_table_alpha, game_table_beta);
        game_table_alpha = game_table_beta;
    }

    ofstream out_file;
    size_t end_file_path = filename.find_last_of('/');
    string out_filename;
    if (end_file_path != string::npos) {
        out_filename = filename.substr(end_file_path+1);
    }
    else {
        out_filename = filename;
    }
    out_file.open("final_output_"+out_filename);
    out_file << "Final Generation: " << generations << "\n";
    for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < width; j++)
            {
                out_file << game_table_alpha[j + (i*width)];
            }
            out_file << "\n";
        }
    out_file.close();
}