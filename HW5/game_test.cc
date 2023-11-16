#include "game_of_life.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    game_of_life game("test1");
    cout << game;
    //cout << "\n" << game.GenWindow(3,8,3,3) << "\n";

    game_of_life game2(game);
    game.NextGen();
    //cout << "\n" << game.GenWindow(3,8,3,3) << "\n";
    
    game.NextGen();
    cout << game;

    game.NextNGen(5);
    cout << game;
    //cout << "\n" << game.GenWindow(3,8,3,3) << "\n";

    game -= 1;
    cout << game;

    game.NextNGen(500);
    cout << game;

    game -= 25;
    cout << game;

    //game_of_life game3("test2");
    //cout << game3;

    //cout << "\n sub window\n" << game.GenWindow(3,3,3,3) << "\n";
    cout << game.GenSubGame(3,2,3,4) << "\n" << ++game.GenSubGame(3,2,3,4) << "\n";

    return 0;
}
