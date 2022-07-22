#include<iostream>
#include"Game.h"

using namespace std;

int main() {
	Game* game = new Game();
	if (game)
	{
		game->Execute();
		delete game;
		game = NULL;
	}
	return 0;
}