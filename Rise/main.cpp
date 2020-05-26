#include <iostream>

#include "Game.h"

int main()
{
    Game game("Rise", 1920, 1080, 120, "Rise/Assets");
    int exitcode = game.Run();

    return exitcode;
}

// Ideas
// 2. do i try to hide asset manager from user for safety
