#include <iostream>

#include "Game.h"

int main()
{
    Game game("Vortex", 900, 600, 30);
    int exitCode = game.Run();

    return exitCode;
}

// Questions
// 1. should i pass a window to the draw functions?

// Ideas
// 1. make drawing shortcut in application class
