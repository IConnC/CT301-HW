#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include "game_of_life.h"

// George Krier - 835973055

using namespace std;

/** game_of_life
 *
 * Instantiates the game of life based on the filename of the starting cells
 *
 */
game_of_life::game_of_life(string filename) : game_of_life(filename, 0) {}

/** game_of_life
 *
 * Instantiates the game of life based on the filename of the file that contains the starting cells and the amount of times to pregenerate the game.
 * Along with this the live cell and dead cells are set to a default * and - respectively
 *
 */
game_of_life::game_of_life(std::string filename, int pregens) : game_of_life(filename, '*', '-', pregens) {}

/** game_of_life
 *
 * Instantiates the game of life based on the filename of the file that contains the starting cells and the live and dead cell characters that we want to use.
 * Does not pregenerate the game of life
 *
 */
game_of_life::game_of_life(std::string filename, char live_cell, char dead_cell) : game_of_life(filename, live_cell, dead_cell, 0) {}

/** game_of_life
 *
 * Instantiates the game of life based on the filename of the file that contains the starting cells and the amount of times to pregenerate the game.
 * Sets the live and dead cell characters according to parameters and pregenerates based on pregens 
 * 
 */
game_of_life::game_of_life(std::string filename, char live_cell, char dead_cell, int pregens) {
    if (live_cell == dead_cell) {
        throw std::runtime_error("game_of_life - game_of_life(std::string, char, char, int) - " + std::string(game_of_life::cell_dupe_error));
    } else {
        this->SetLiveCell(live_cell);
        this->SetDeadCell(dead_cell);
    }
    fstream file_in(filename);
    if (!file_in) {
        throw(runtime_error("game_of_life - game_of_life(std::string, char, char, int) - " + std::string(game_of_life::file_not_found_error+filename+game_of_life::error_end)));
    }
    if (!(file_in >> this->width_ >> this->height_)) {
        throw(runtime_error("game_of_life - game_of_life(std::string, char, char, int) - " + std::string(game_of_life::invalid_read_error+filename+game_of_life::error_end)));
    }
    this->current_ = string(this->width_*this->height_, this->dead_cell_);
    string line;
    getline(file_in, line);
    for (int row = 0; row < this->height_; ++row) {
        getline(file_in, line);
        for (int col = 0; col < this->width_; ++col) {
            if (line[col] == '*') {
                this->current_[col+(row*this->width_)] = this->live_cell_;
            }
        }
    }
    this->NextNGen(pregens);
}

/** game_of_life
 *
 * Instantiates the game of life based on the window given as a string and sets the row, columns, height, width, live_cell, and dead_cell to the respective parameter.
 * Does not pregenerate
 *
 */
game_of_life::game_of_life(std::string window, int height, int width, char live_cell, char dead_cell) {
    if (live_cell == dead_cell) {
        throw std::runtime_error("game_of_life - game_of_life(std::string, int, int, int, int, char, char) - " + std::string(game_of_life::cell_dupe_error));
    } else {
        this->SetLiveCell(live_cell);
        this->SetDeadCell(dead_cell);
    }
    height_ = height;
    width_ = width;
    this->current_ = window;
}

/** SetLiveCell
 *
 * Sets the live_cell character to a new character
 *
 */
void game_of_life::SetLiveCell(char new_live_cell) {
    if (new_live_cell == this->dead_cell_) {
        throw(runtime_error("game_of_life - SetLiveCell(char) - " + std::string(game_of_life::cell_dupe_error)));
    }
    replace(this->current_.begin(), this->current_.end(), this->live_cell_, new_live_cell);
    this->live_cell_ = new_live_cell;
}

/** SetDeadCell
 *
 * Sets the dead_cell character to a new character
 *
 */
void game_of_life::SetDeadCell(char new_dead_cell) {
    if (new_dead_cell == this->live_cell_) {
        throw(runtime_error("game_of_life - SetDeadCell(char) - " + std::string(game_of_life::cell_dupe_error)));
    }
    replace(this->current_.begin(), this->current_.end(), this->dead_cell_, new_dead_cell);
    this->dead_cell_ = new_dead_cell;
}

/** GetGenerations
 *
 * Returns the current generation that we have generated to
 *
 */
int game_of_life::GetGenerations() {
    return this->generations_;
}

/** NextGen
 *
 * Generates the next generation and updates the current game board
 * The method also adds the current save state to the that discards the oldest save and only saves 100 iterations
 *
 */
void game_of_life::NextGen() {
    if (save_state_index >= 99) {
        for (int i=0; i < 99; i++) {
            save_states[i] = save_states[i+1];
        }
        save_state_index--;
    }
    save_states[++save_state_index] = CreateSaveState(*this);

    ++this->generations_;
    string next = this->current_;
    for (int row = 0; row < this->height_; ++row) {
        for (int col = 0; col < this->width_; ++col) {
            short neighbor_count = 0;
            int tr, br, lc, rc;
            if (row == 0)
                tr = this->height_ - 1;
            else
                tr = row - 1;
            if (row+1 == this->height_)
                br = 0;
            else
                br = row+1;
            if (col == 0)
                lc = this->width_ - 1;
            else
                lc = col - 1;
            if (col+1 == this->width_)
                rc = 0;
            else
                rc = col + 1;
            int neighbors[8] = {tr*this->width_ + lc, tr*this->width_ + col, tr*this->width_ + rc,
                            row*this->width_+lc, row*this->width_ + rc, br*this->width_ + lc, 
                            br*this->width_+col, br*this->width_+rc};
            for (size_t j = 0; j < 8; j++) {
                if (this->current_[neighbors[j]] == this->live_cell_)
                    ++neighbor_count;
            }
            int curr = col+(row*this->width_);
            if (this->current_[curr] == this->live_cell_) {
                if(neighbor_count == 2 || neighbor_count == 3)
                    next[curr] = this->live_cell_;
                else
                    next[curr] = this->dead_cell_;
            }
            else {
                if(neighbor_count == 3)
                    next[curr] = this->live_cell_;
                else
                    next[curr] = this->dead_cell_;
            }
        }
    }
    this->current_ = next;
}

/** NextNGen
 *
 * Generates the next n generations and updates the current game board
 * Utilizes call to NextGen to prevent repeat code
 *
 */
void game_of_life::NextNGen(int n) {
    while (n-- > 0) {
        this->NextGen();
    }
}

/** GenWindow
 *
 * Generates a window where the row and column provided are the top left most part of the window. The window is then sized with a height and width.
 * The height and width may cause the method to loop around to the otherside of the game board.
 *
 */
std::string game_of_life::GenWindow(int row, int col, int height, int width) {
    if (height > height_ || width > width_)
        throw domain_error(game_oob);

    if (row > height_ || col > width_)
        throw range_error("game_of_life - GenWindow(int, int, int, int) - " + std::string(row_col_oob_1) + std::to_string(row)
         + std::string(row_col_oob_2) + std::to_string(col) + std::string(row_col_oob_3) + std::to_string(width_)
         + std::string(row_col_oob_4) + std::to_string(height_) + std::string(row_col_oob_5));
    
    std::string window = "";
    int real_index;

    for (int window_row=0; window_row < height; window_row++) {
        for (int window_col=0; window_col < width; window_col++) {        
            real_index = ((col + window_col) % width_ + (((row + window_row) % height_) * width_)); // Wrap around logic
            window += current_[real_index];
        }
    }
    return window;
}

/** GenSubGame
 *
 * Generates a "sub game" or new instance of game_of_life that uses a window that is generated using the parameters 
 * and a call to GenWindow instead of grabbing the starting cells from a file.
 *
 */
game_of_life game_of_life::GenSubGame(int row, int col, int height, int width) {
    if (height > height_ || width > width_)
        throw domain_error(game_oob);

    if (row > height_ || col > width_)
        throw range_error("game_of_life - GenSubGame(int, int, int, int) - " + std::string(row_col_oob_1) + std::to_string(row)
         + std::string(row_col_oob_2) + std::to_string(col) + std::string(row_col_oob_3) + std::to_string(width_)
         + std::string(row_col_oob_4) + std::to_string(height_) + std::string(row_col_oob_5));

    std::string window = GenWindow(row, col, height, width);
    game_of_life gol(window, height, width, live_cell_, dead_cell_);
    return gol;
}

/** ToggleCell
 *
 * Sets a live cell to dead or a dead cell to a live cell based on an index
 *
 */
void game_of_life::ToggleCell(int index) {
    if (index > width_ * height_)
        throw range_error("Index out of bounds, index passed: " + std::to_string(index) + ", maximum index: " + std::to_string(width_ * height_ - 1) + "\n");
    if (current_[index] == dead_cell_) {
        current_[index] = dead_cell_;
    } else {
        current_[index] = live_cell_;
    }
}

/** ToggleCell
 *
 * Sets a live cell to dead or a dead cell to a live cell based on the row and column a cell exists at
 *
 */
void game_of_life::ToggleCell(int row, int col) {
    if (row > height_ || col > width_)
        throw range_error("game_of_life - ToggleCell(int, int) - " + std::string(row_col_oob_1) + std::to_string(row)
         + std::string(row_col_oob_2) + std::to_string(col) + std::string(row_col_oob_3) + std::to_string(width_)
         + std::string(row_col_oob_4) + std::to_string(height_) + std::string(row_col_oob_5));
    
    ToggleCell(col % width_ + ((row % height_) * width_));
}

/** IsStillLife
 *
 * If the game board does not change from one generation to another we return true meaning the game is "still"
 *
 */
bool game_of_life::IsStillLife() {
    return current_ == (this->operator+(1)).current_; // If current generation is equal to next generation return true
}

/** GetAvailableGens
 *
 * Returns the number of generations that can be rolled back
 *
 */
int game_of_life::GetAvailableGens() {
    return save_state_index;
}

/** CreateSaveState
 *
 * Creates a save state based on the provided instance of game_of_life (game_save_state)
 *
 */
game_save_state game_of_life::CreateSaveState(game_of_life& instance) {
    return CreateSaveState(instance.current_, instance.width_, instance.height_, instance.generations_, instance.live_cell_, instance.dead_cell_);
}

/** CreateSaveState
 *
 * Creates a save state based on the provided game_board and game_board details of game_of_life (game_save_state)
 *
 */
game_save_state game_of_life::CreateSaveState(std::string game_board, int width, int height, int generation, char live, char dead) {
    struct game_save_state temp;
    temp.game_board = game_board;
    temp.width = width;
    temp.height = height;
    temp.generation = generation;
    temp.live = live;
    temp.dead = dead;
    return temp;
}

/** operator++
 *
 * Incremenets the current game by 1 generation
 *
 */
game_of_life& game_of_life::operator++() { // Pre increment
    this->NextGen();
    return *this;
}

/** operator++
 *
 * Returns a copy of the game before incrementing the game by 1 generation
 *
 */
game_of_life game_of_life::operator++(int fake) { // Post increment
    const auto old = *this;
    ++*this;
    return old;
}

/** operator+=
 *
 * Increments or rolls back the game by gens generations then returns a reference to the current game
 *
 */
game_of_life& game_of_life::operator+=(int gens) {
    if (gens >= 0) {
        NextNGen(gens);
    } else {
        operator-=(abs(gens));
    }
    return *this;
}

/** operator-=
 *
 * Rolls back the game by gens generations and returns the reference to the current game
 *
 */
game_of_life& game_of_life::operator-=(int gens) {
    if (save_state_index == 0) throw domain_error("game_of_life - operator-=(int) - " + std::string(domain_error_no_rollback));
    if (gens > save_state_index + 1) throw range_error("game_of_life - operator-=(int) - " + std::string(range_error_lack_generations));
    
    save_state_index -= (gens - 1);
    
    struct game_save_state temp = save_states[save_state_index];

    this->current_ = temp.game_board;
    this->width_ = temp.width;
    this->height_ = temp.height;
    this->generations_ = temp.generation;
    this->live_cell_ = temp.live;
    this->dead_cell_ = temp.dead;

    return *this;
}

/** operator+
 *
 * Increments or rolls back a copy of the game by gens generations then returns the copy.
 * This does not affect the current instance
 *
 */
game_of_life game_of_life::operator+(int gens) {
    game_of_life res = *this;
    if (gens >= 0) {
        res.NextNGen(gens);
    } else {
        return res.operator-(abs(gens));
    }
    return res;
}

/** operator-
 *
 * Rolls back a copy of the game by gens generations
 * This does not affect the current instance
 *
 */
game_of_life game_of_life::operator-(int gens) {
    if (save_state_index == 0) throw domain_error("game_of_life - operator-(int) - " + std::string(domain_error_no_rollback));
    if (gens > save_state_index) throw range_error("game_of_life - operator-(int) - " + std::string(range_error_lack_generations));

    game_of_life res = *this;
    res -= gens;

    return res;
}

/** operator--
 *
 * Decrement the current game state by 1 then returns a reference to the current decremented game state
 * Pre-Decrement
 *
 */
game_of_life& game_of_life::operator--() {
    if (save_state_index == 0) throw domain_error("game_of_life - operator--() - " + std::string(domain_error_no_rollback));
    operator-=(1);
    return *this;
}

/** operator--
 *
 * Returns a copy of the current game before decrementing the current instance of the game by 1
 * Post-Decrement
 * 
 */
game_of_life game_of_life::operator--(int fake) {
    if (save_state_index == 0) throw domain_error("game_of_life - operator--(int) - " + std::string(domain_error_no_rollback));

    game_of_life old = *this;
    operator-=(1);
    return old;
}

/** CalculateLiveCellRatio
 *
 * Calculates the percentage of alive cells that are in the game board.
 * If 25 cells are alive out of 100 cells, the percentage of alive cells would be 25% (in float format)
 *
 */
float game_of_life::CalculateLiveCellRatio(std::string game_board) {
    if (game_board.size() == 0) return 0;

    int num_alive = 0;
    for (int i=0; i < static_cast<int>(game_board.size()); i++) {
        if (game_board[i] == live_cell_)
            num_alive++;
    }
    return (static_cast<float>(num_alive) / game_board.size()) * 100.0f;
}

/** operator<
 *
 * If the current game of life instance has less live cells than the game of life instance that is provided, return true, else false
 *
 */
bool game_of_life::operator<(game_of_life &gol) {
    return CalculateLiveCellRatio(current_) < CalculateLiveCellRatio(gol.current_);
}

/** operator<=
 *
 * If the current game of life instance has less or equal live cells than the game of life instance that is provided, return true, else false
 *
 */
bool game_of_life::operator<=(game_of_life &gol) {
    return CalculateLiveCellRatio(current_) < CalculateLiveCellRatio(gol.current_);
}

/** operator
 *
 * If the current game of life instance has more live cells than the game of life instance that is provided, return true, else false
 *
 */
bool game_of_life::operator>(game_of_life &gol) {
    return CalculateLiveCellRatio(current_) > CalculateLiveCellRatio(gol.current_);
}

/** operator>=
 *
 * If the current game of life instance has more or equal live cells than the game of life instance that is provided, return true, else false
 *
 */
bool game_of_life::operator>=(game_of_life &gol) {
    return CalculateLiveCellRatio(current_) >= CalculateLiveCellRatio(gol.current_);
}

/** operator==
 *
 * If the current game of life instance and the provided instance have a Alive Cell Ratio of less than or equal to 0.5, return true, else false
 *
 */
bool game_of_life::operator==(game_of_life &gol) {
    return std::fabs(CalculateLiveCellRatio(current_) - CalculateLiveCellRatio(gol.current_)) <= 0.5f;
}

/** operator<<
 *
 * Outputs the game of life game board as a string formatted as such:
 * Generation: X
 * -----*-*--
 * ------**--
 * ------***-
 * --------*-
 * ---*--*---
 * Where X is replaced by the current generation and the game board is made of live_cell and dead_cell and simulated to the desired generation.
 */
std::ostream& operator<<(std::ostream& os, const game_of_life& game) {
    string out = "Generation: ";
    out += to_string(game.generations_);
    out += '\n';
    for (int row = 0; row < game.height_; ++row) {
        for (int col = 0; col < game.width_; ++col) {
            out += game.current_[col+(row*game.width_)];
        }
        out += '\n';
    }
    os << out;
    return os;
}