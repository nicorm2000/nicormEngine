#include "Game/Game.h"

int main() {
    Game* game = new Game();
    if (game) {
        game->Init();
        game->Deinit();
        delete game;
    }
	return 0;
}