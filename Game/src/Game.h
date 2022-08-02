#ifndef GAME_H
#define GAME_H

#include"base.h" 
#include <vector>

using namespace Engine;

class Game: public Base {
private:
	float angle = 0;
	float t = 0;
	glm::vec2 shapePos = glm::vec2(0,0);
	Sprite* _sprite = NULL;
	Animation* player = NULL;
	Tilemap* map = NULL;

public:
	Game();
	~Game();
	void PlayerInputs();
	void InitGame() override;
	void UpdateGame() override;
	void UnloadGame() override;
};

#endif