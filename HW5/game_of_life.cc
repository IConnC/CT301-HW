#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "game_of_life.h"

// George Krier - 835973055

using namespace std;

//⁣⁢⁢⁣Constructors
game_of_life::game_of_life(string filename) : game_of_life(filename, 0) {}

game_of_life::game_of_life(std::string filename, int pregens) : game_of_life(filename, '*', '-', pregens) {}

game_of_life::game_of_life(std::string filename, char live_cell, char dead_cell) : game_of_life(filename, live_cell, dead_cell, 0) {}

game_of_life::game_of_life(std::string filename, char live_cell, char dead_cell, int pregens) {
    if (live_cell == dead_cell) {
        throw std::runtime_error("game_of_life - game_of_life(std::string, char, char, int) - " + std::string(game_of_life::cell_dupe_error));
    }
    else {
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

//⁣⁢⁢⁣Mutators and Accessors
void game_of_life::SetLiveCell(char new_live_cell) {
    if (new_live_cell == this->dead_cell_) {
        throw(runtime_error("game_of_life - SetLiveCell(char) - " + std::string(game_of_life::cell_dupe_error)));
    }
    replace(this->current_.begin(), this->current_.end(), this->live_cell_, new_live_cell);
    this->live_cell_ = new_live_cell;
}

void game_of_life::SetDeadCell(char new_dead_cell) {
    if (new_dead_cell == this->live_cell_) {
        throw(runtime_error("game_of_life - SetDeadCell(char) - " + std::string(game_of_life::cell_dupe_error)));
    }
    replace(this->current_.begin(), this->current_.end(), this->dead_cell_, new_dead_cell);
    this->dead_cell_ = new_dead_cell;
}

int game_of_life::GetGenerations() {
    return this->generations_;
}

//⁣⁢⁢⁣​Next Generations
void game_of_life::NextGen() {
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
    save_states[save_state_index++] = CreateSaveState(*this);
}

void game_of_life::NextNGen(int n) {
    while (n-- > 0) {
        this->NextGen();
    }
}

std::string game_of_life::GenWindow(int row, int col, int height, int width) {
    if (height > height_ || width > width_)
        throw domain_error(game_oob);

    if (row > height_ || col > width_)
        throw range_error(std::string(row_col_oob_1) + std::to_string(row)
         + std::string(row_col_oob_2) + std::to_string(col) + std::string(row_col_oob_3) + std::to_string(width)
         + std::string(row_col_oob_4) + std::to_string(height) + std::string(row_col_oob_5));
    
    std::string window = "";

    int real_index;

    //cout << "\nGame Table Height: " << height_ << "\nGame Table Width: " << width_ << "\nStarting Row: " 
     //    << row << "\nStarting Col: " << col << "\nWindow Height: " << height << "\nWindow Width: " << width << "\n\n";  

    for (int window_row=0; window_row < height; window_row++) {
        for (int window_col=0; window_col < width; window_col++) {

            //cout << "Window Row: " << window_row << "\nWindow Col: " << window_col << "\n";
            
            real_index = ((col + window_col) % width_ + (((row + window_row) % height_) * width_));
            //cout << "Real Index: " << real_index << "\n\n";
            window += current_[real_index];
        }
    }
    return window;
}



game_save_state game_of_life::CreateSaveState(game_of_life& instance) {
    return CreateSaveState(instance.current_, instance.width_, instance.height_, instance.generations_, instance.live_cell_, instance.dead_cell_);
}

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

//⁣⁢⁢⁣Operators
game_of_life& game_of_life::operator++() {
    this->NextGen();
    return *this;
}

game_of_life game_of_life::operator++(int fake) {
    const auto old = *this;
    ++*this;
    return old;
}

game_of_life& game_of_life::operator+=(int gens) {
    if (gens >= 0) {
        NextNGen(gens);
    }
    else {
        operator-=(abs(gens));
    }
    return *this;
}

game_of_life& game_of_life::operator-=(int gens) {
    if (save_state_index == 0) throw domain_error("game_of_life - operator-=(int) - " + std::string(domain_error_no_rollback));
    if (gens > save_state_index) throw range_error("game_of_life - operator-=(int) - " + std::string(range_error_lack_generations));

    save_state_index -= gens;
    struct game_save_state temp = save_states[save_state_index];

    this->current_ = temp.game_board;
    this->width_ = temp.width;
    this->height_ = temp.height;
    this->generations_ = temp.generation;
    this->live_cell_ = temp.live;
    this->dead_cell_ = temp.dead;

    return *this;
}

game_of_life game_of_life::operator+(int gens) {
    game_of_life res = *this;
    if (gens >= 0) {
        res.NextNGen(gens);
    } else {
        return operator-(abs(gens));
    }
    this->NextNGen(gens);
    return res;
}

game_of_life game_of_life::operator-(int gens) {
    if (save_state_index == 0) throw domain_error("game_of_life - operator-(int) - " + std::string(domain_error_no_rollback));
    if (gens > save_state_index) throw range_error("game_of_life - operator-(int) - " + std::string(range_error_lack_generations));

    game_of_life res = *this;
    res -= gens;

    return res;
}

/*
Decrement the current game state by 1 then returns a reference to the current decremented game state
*/
game_of_life& game_of_life::operator--() {
    if (save_state_index == 0) throw domain_error("game_of_life - operator--() - " + std::string(domain_error_no_rollback));
    operator-=(1);
    return *this;
}

game_of_life game_of_life::operator--(int fake) {
    if (save_state_index == 0) throw domain_error("game_of_life - operator--(int) - " + std::string(domain_error_no_rollback));

    game_of_life old = *this;
    operator-=(1);
    return old;
}


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
