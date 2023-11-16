#ifndef GAME_OF_LIFE_H_DEFINED
#define GAME_OF_LIFE_H_DEFINED
#include <string>
#include <iostream>

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
    * @Return The current game string should be initialized according to the contents of filename with default live a dead cell characters and initialized generation to 0
    */
    game_of_life(std::string filename);
    
    /** game_of_life
    * @Param filename - The input filename to read for the starting conditions of The Game of Life
    * @Param pregens - Generations to pre-simulate during initialization
    * @Return The current game string should be initialized according to the contents of filename with default live a dead cell characters and initialized generation to 0
    *         The game should also pre-generate/simulate for pregens number of cycles
    */
    game_of_life(std::string filename, int pregens);
    
    /** game_of_life
    * @Param filename - The input filename to read for the starting conditions of The Game of Life
    * @Param live_cell - The character that should be used to represent a live cell
    * @Param live_cell - The character that should be used to represent a dead cell
    * @Return The current game string should be initialized according to the contents of filename with live cells set to live_cell and dead cells set to dead_cell
    *         characters and initialized generation to 0
    */
    game_of_life(std::string filename, char live_cell, char dead_cell);
    
    /** game_of_life
    * @Param filename - The input filename to read for the starting conditions of The Game of Life
    * @Param live_cell - The character that should be used to represent a live cell
    * @Param live_cell - The character that should be used to represent a dead cell
    * @Param pregens - Generations to pre-simulate during initialization
    * @Return The current game string should be initialized according to the contents of filename with live cells set to live_cell and dead cells set to dead_cell
    *         The game should also pre-generate/simulate for pregens number of cycles
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

    /** GenWindow
    * @Param row - Row number of index to set as top left of the window
    * @Param col - Column number of index to set as top left of the window
    * @Param height - Height to set the window
    * @Param width - Width the set the window
    * @Return string of the game table that is a subset of the original game table but offset by the row and column and set with height rows and width columns
    */
    std::string GenWindow(int row, int col, int height, int width);
    
    /** GenSubGame
    * @Param dead_cell - The character that should be used to represent a dead cell
    * @Return None
    */
    game_of_life GenSubGame(int row, int col, int height, int width);

    /** ToggleCell
    * @Param index - The index of the cell to toggle
    * @Return None
    */
    void ToggleCell(int index);

    /** ToggleCell
    * @Param row - The row of the cell to toggle
    * @Param col - The column of the cell to toggle
    * @Return None
    */
    void ToggleCell(int row, int col);
    
    /** IsStillLife
    * @Param None
    * @Return None
    */
    bool IsStillLife();

    /** GetAvailableGens
    * @Param None
    * @Return The number of generations that we are able to rollback to
    */
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

    /** operator+=
    * @Param gens - number of generations to generator or rollback
    * @Return Returns instance of current game after incrementing by gens generations
    */
    game_of_life& operator+=(int gens);

    /** operator-=
    * @Param gens - number of gens to rollback
    * @Return Returns instance of current game after rolling back by gens generations
    */
    game_of_life& operator-=(int gens);

    /** operator+
    * @Param gens - Number of generations to rollback
    * @Return Copy of game_of_life incremented by number of gens
    */
    game_of_life operator+(int gens);

    /** operator-
    * @Param gens - Number of generations to increment/simulate
    * @Return Copy of game_of_life rolled back by number of gens
    */
    game_of_life operator-(int gens);

    /** operator--
    * @Param None
    * @Return Rolls back current game by 1 then returns current instance
    */
    game_of_life& operator--();

    /** operator--
    * @Param None
    * @Return Copy of game state before rolling back by 1
    */
    game_of_life operator--(int fake);

    /** operator<
    * @Param game of life instance to compare to
    * @Return true if number of live cells in current instance less than provided instance else false
    */
    bool operator<(game_of_life& gol);
    
    /** operator<=
    * @Param game of life instance to compare to
    * @Return true if number of live cells in current instance less than or equal to provided instance else false
    */
    bool operator<=(game_of_life& gol);
    
    /** operator>
    * @Param game of life instance to compare to
    * @Return true if number of live cells in current instance greater than provided instance else false
    */
    bool operator>(game_of_life& gol);

    /** operator>=
    * @Param game of life instance to compare to
    * @Return true if number of live cells in current instance greater than or equal to provided instance else false
    */
    bool operator>=(game_of_life& gol);

    /** operator>
    * @Param game of life instance to compare to
    * @Return true if number of live cells in current instance and live cells in provided instance within 0.5% of each other else false
    */
    bool operator==(game_of_life& gol);

    /** operator<<
    * @Param os - ostream from the right side of the operator
    * @Param game - the game of life object to output
    * @Return ostream with the game_of_life string formatting requirements appended to it
    */
    friend std::ostream& operator<<(std::ostream& os, const game_of_life& game);

private:
    /** game_of_life
    * @Param window - string containing everything on the gameboard with no whitespace or new line
    * @Param height - Height of the game board
    * @Param width - Width of the game board
    * @Param live_cell - What to set the live cell character to
    * @Param dead_cell - What to set the dead cell character to
    * @Return Should initialize a new game of life instance with the inputs of a window
    */
    game_of_life(std::string window, int height, int width, char live_cell, char dead_cell);

    /** CalculateLiveCellRatio
    * @Param game_board - Game board to calculate percentage with
    * @Return Float that is the calculation of the percentage of cells that are currently alive compared to the total cells
    */
    float CalculateLiveCellRatio(std::string game_board);
    
    /** CreateSaveState
    * @Param instance - game_of_life instance to create a save state for
    * @Return a game_save_state that is created based on instance
    */
    game_save_state CreateSaveState(game_of_life& instance);
    
    /** CreateSaveState
    * @Param game_board - Game board to create the save state off of
    * @Param width - Width of the game board
    * @Param height - Height of the game board
    * @Param generation - Current generation to save into the save state
    * @Param live - Live cell character to save into the save state
    * @Param dead - Dead cell character to save into the save state
    * @Return a game_save_state that is created based on the attributes of game_board and other parameters
    */
    game_save_state CreateSaveState(std::string game_board, int width, int height, int generation, char live, char dead);
};

#endif