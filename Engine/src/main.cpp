#include "base.h"

using namespace Engine;

class Game : public Base {
private:
	Shape* shape = NULL;
public:
	Game();
	~Game();
	void Init() override;
	void Update() override;
	void Unload() override;
};

Game::Game() {
}

Game::~Game() {
	if (shape != NULL) {
		delete shape;
		shape = NULL;
	}
}

void Game::Init() {
	shape = new Engine::Shape(Type::triangle, _renderer, basicShader);
	shape->Init();
}

void Game::Update() {
	shape->Draw();
}

void Game::Unload() {
	if (shape != NULL) {
		delete shape;
		shape = NULL;
	}
}

int main() {

	Game* game = new Game();
	if (game)
	{
		game->InitEngine();
		game->Init();
		game->UpdateEngine();
		game->Unload();
		game->UnloadEngine();
	}
	return 0;
}