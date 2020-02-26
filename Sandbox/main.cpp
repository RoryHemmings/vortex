#include <iostream>

#include "Game.h"

int main()
{
    Game game("Vortex", 900, 600, 30);
    int exitCode = game.Run();

    return exitCode;
}
