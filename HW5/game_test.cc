#include "game_of_life.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    game_of_life game("test1");
    cout << game;
    //cout << "\n" << game.GenWindow(3,8,3,3) << "\n";

    game.NextGen();
    //cout << game;
    //cout << "\n" << game.GenWindow(3,8,3,3) << "\n";


    game.NextNGen(5);
    cout << game;
    //cout << "\n" << game.GenWindow(3,8,3,3) << "\n";

    return 0;
}
