#include <iostream>

#include "Game.h"

int main()
{
    Game game("Vortex", 900, 600, 30, "Sandbox/Assets");
    int exitCode = game.Run();

    return exitCode;
}

// Questions
// 1. should i pass a window to the draw functions?
// 2. Do i define return types as references?

// Ideas
// 1. make drawing shortcut in application class
// 2. do i try to hide asset manager from user for safety
// 3. What is a way to not have each path explicitly listed as a parameter
// 4. What do i do about singletons with the game state
