#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "game_of_life.h"
//⁣⁢⁢⁣Includes as needed for functionality

using namespace std;

//⁣⁢⁢⁣Constructors
game_of_life::game_of_life(string filename) : 
    game_of_life(filename, 0) {}
game_of_life::game_of_life(std::string filename, int pregens) :
    game_of_life(filename, '*', '-', pregens) {}
game_of_life::game_of_life(std::string filename, char live_cell, char dead_cell) : 
    game_of_life(filename, live_cell, dead_cell, 0) {}
game_of_life::game_of_life(std::string filename, char live_cell, char dead_cell, int pregens)
    {
        if (live_cell == dead_cell) {
            throw(runtime_error(game_of_life::cell_dupe_error));
        }
        else {
            this->SetLiveCell(live_cell);
            this->SetDeadCell(dead_cell);
        }
        fstream file_in(filename);
        if (!file_in) {
            throw(runtime_error(game_of_life::file_not_found_error+filename+game_of_life::error_end));
        }
        if (!(file_in >> this->width_ >> this->height_)) {
            throw(runtime_error(game_of_life::invalid_read_error+filename+game_of_life::error_end));
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
        throw(runtime_error(game_of_life::cell_dupe_error));
    }
    replace(this->current_.begin(), this->current_.end(), this->live_cell_, new_live_cell);
    this->live_cell_ = new_live_cell;
}
void game_of_life::SetDeadCell(char new_dead_cell) {
    if (new_dead_cell == this->live_cell_) {
        throw(runtime_error(game_of_life::cell_dupe_error));
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
}
void game_of_life::NextNGen(int n) {
    while (n-- > 0) {
        this->NextGen();
    }
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
game_of_life& game_of_life::operator+(int gens) {
    this->NextNGen(gens);
    return *this;
}
string game_of_life::ToString() const {
    string out = "Generation: ";
    out += to_string(this->generations_);
    out += '\n';
    for (int row = 0; row < this->height_; ++row) {
        for (int col = 0; col < this->width_; ++col) {
            out += this->current_[col+(row*this->width_)];
        }
        out += '\n';
    }
    return out;
}
std::ostream & operator<<(std::ostream &os, const game_of_life &game) {
    return os << game.ToString();
} 
