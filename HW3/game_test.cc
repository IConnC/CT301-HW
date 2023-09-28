#include "game_of_life.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    game_of_life game("fail");
    cout << game;
    game.NextGen();
    cout << game;
    game.NextNGen(5);
    cout << game;
    return 0;
}
