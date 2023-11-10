#ifndef GAME_OF_LIFE_H_DEFINED
#define GAME_OF_LIFE_H_DEFINED
#include <string>
#include <iostream>
class game_of_life {
	//⁣⁢⁢⁣Data Member Variables
    int height_, width_;
    int generations_=0;
    char live_cell_='*',dead_cell_='-';
    std::string current_;
	constexpr static const char * cell_dupe_error = "game_of_life - Live Cell and Dead Cell cannot be the same character\n";
	constexpr static const char * file_not_found_error = "game_of_life - File Not Found \"";
	constexpr static const char * invalid_read_error = "game_of_life - Width and Height incorrectly formatted for file \"";
	constexpr static const char * error_end = "\"\n";
	//⁣⁢⁢⁣Invalid read and FNF error need to include the offending file name and be closed off by the error end string
public:
    game_of_life() = delete;
    //⁣⁢⁢⁣All Constructors throw runtime errors , File not Found, Invalid Width and Height, Live and Dead Cell duplication
    game_of_life(std::string filename);
    game_of_life(std::string filename, int pregens);
    game_of_life(std::string filename, char live_cell, char dead_cell);
    game_of_life(std::string filename, char live_cell, char dead_cell, int pregens);
    int GetGenerations();
    void NextGen();
    void NextNGen(int n);
	//⁣⁢⁢⁣Setting the Live and Dead cells both throw runtime errors if the one is trying to be set to the other
    void SetLiveCell(char live_cell);
    void SetDeadCell(char dead_cell);
    game_of_life& operator+(int gens); //⁣⁢⁢⁣Simple addition
    game_of_life& operator++(); //⁣⁢⁢⁣Pre-increment
    game_of_life operator++(int fake); //⁣⁢⁢⁣Post-increment
    std::string ToString() const;

};
std::ostream & operator<<(std::ostream &os, const game_of_life &game);
#endif