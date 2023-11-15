#ifndef GAME_OF_LIFE_H_DEFINED
#define GAME_OF_LIFE_H_DEFINED
#include <string>
#include <iostream>



// TODO: Constructor comments the output should be an explanation of what the object looks like after completing the constructor call

struct game_save_state {
    std::string game_board;
    int width;
    int height;
    int generation;
    char live;
    char dead;
};

class game_of_life {
	//⁣⁢⁢⁣Data Member Variables
    int height_, width_;
    int generations_=0;
    char live_cell_='*',dead_cell_='-';
    std::string current_;

    // Save State Data
    game_save_state save_states[100];
	int save_state_index = 0;

    // oob - out of bounds
    constexpr static const char * cell_dupe_error = "Live Cell and Dead Cell cannot be the same character\n";
	constexpr static const char * file_not_found_error = "File Not Found \"";
	constexpr static const char * invalid_read_error = "Width and Height incorrectly formatted for file \"";
    constexpr static const char * error_end = "\"\n";
    constexpr static const char * domain_error_no_rollback = "No generations available to roll back to.\n";
    constexpr static const char * game_oob = "The height/width supplied is out of game bounds.\n";
    constexpr static const char * range_error_lack_generations = "Number of generations passed is greater than the available generations to rollback to.\n";
	constexpr static const char * row_col_oob_1 = "Index out of Bounds for row: ";
	constexpr static const char * row_col_oob_2 = ", column: ";
	constexpr static const char * row_col_oob_3 = ", Max values are row: ";
    constexpr static const char * row_col_oob_4 = ", col: ";
    constexpr static const char * row_col_oob_5 = ".\n";
	//⁣⁢⁢⁣Invalid read and FNF error need to include the offending file name and be closed off by the error end string
public:
    game_of_life() = delete;
    //⁣⁢⁢⁣All Constructors throw runtime errors , File not Found, Invalid Width and Height, Live and Dead Cell duplication
    
    /** game_of_life
    * @Param filename - The input filename to read for the starting conditions of The Game of Life
    * @Return None
    */
    game_of_life(std::string filename);
    
    /** game_of_life
    * @Param filename - The input filename to read for the starting conditions of The Game of Life
    * @Param pregens - Generations to pre-simulate during initialization
    * @Return None
    */
    game_of_life(std::string filename, int pregens);
    
    /** game_of_life
    * @Param filename - The input filename to read for the starting conditions of The Game of Life
    * @Param live_cell - The character that should be used to represent a live cell
    * @Param live_cell - The character that should be used to represent a dead cell
    * @Return None
    */
    game_of_life(std::string filename, char live_cell, char dead_cell);
    
    /** game_of_life
    * @Param filename - The input filename to read for the starting conditions of The Game of Life
    * @Param live_cell - The character that should be used to represent a live cell
    * @Param live_cell - The character that should be used to represent a dead cell
    * @Param pregens - Generations to pre-simulate during initialization
    * @Return None
    */
    game_of_life(std::string filename, char live_cell, char dead_cell, int pregens);
    
    /** GetGenerations
    * @Param None
    * @Return Number of generations
    */
    int GetGenerations();
    
    /** NextGen
    * @Param None
    * @Return None
    */
    void NextGen();
    
    /** NextNGen
    * @Param n - Number of generations to simulate
    * @Return None
    */
    void NextNGen(int n);
    

	//⁣⁢⁢⁣Setting the Live and Dead cells both throw runtime errors if the one is trying to be set to the other

    /** SetLiveCell
    * @Param live_cell - The character that should be used to represent a live cell
    * @Return None
    */
    void SetLiveCell(char live_cell);
    
    /** SetDeadCell
    * @Param dead_cell - The character that should be used to represent a dead cell
    * @Return None
    */
    void SetDeadCell(char dead_cell);

    std::string GenWindow(int row, int col, int height, int width);
    
    game_of_life GenSubGame(int row, int col, int ght, int width);

    void ToggleCell(int index);

    void ToggleCell(int row, int col);
    
    bool IsStillLife();

    int GetAvailableGens();

    /** operator++
    * @Param None
    * @Return game_of_life reference after completing one generation simulation
    */
    game_of_life& operator++(); //⁣⁢⁢⁣Pre-increment

    /** operator++
    * @Param fake - fake
    * @Return Old Instance of game_of_life before completing one generation simulation
    */
    game_of_life operator++(int fake); //⁣⁢⁢⁣Post-increment
    
    game_of_life& operator+=(int gens);

    game_of_life& operator-=(int gens);

    /** operator+
    * @Param gens - Number of generations to increment/simulate
    * @Return Copy of game_of_life then incremented by number of gens
    */
    game_of_life operator+(int gens);

    game_of_life operator-(int gens);

    game_of_life& operator--();

    game_of_life operator--(int fake);


    bool operator<(game_of_life &);
    
    bool operator<=(game_of_life &);
    
    bool operator>(game_of_life &);
    
    bool operator>=(game_of_life &);

    bool operator==(game_of_life &);

    /** operator<<
    * @Param os - ostream from the right side of the operator
    * @Param game - the game of life object to output
    * @Return ostream with the game_of_life ToString method's returned string appended to it
    */
    friend std::ostream& operator<<(std::ostream& os, const game_of_life& game);

private:
    game_save_state CreateSaveState(game_of_life& instance);
    game_save_state CreateSaveState(std::string game_board, int width, int height, int generation, char live, char dead);
};

#endif