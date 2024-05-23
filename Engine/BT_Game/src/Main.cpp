#include "Game/Game.h"

void main()
{
    Game* game = new Game();
    game->Run();
    delete game;
}