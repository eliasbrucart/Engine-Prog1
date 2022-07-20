#include<iostream>
#include"Game.h"
using namespace std;

int main() {
	Game* game = new Game();
	if (game)
	{
		game->Init();
		game->Update();
		game->Unload();
		delete game;
		game = NULL;
	}
	return 0;
}