#include "Game.h"

Game::Game() {

}
Game::~Game() {
	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}
	if (!shapes.empty()) {
		for (int i = 0; i < shapes.size(); i++) {
			if (shapes[i]) {
				delete shapes[i];
				_shape = NULL;
			}
		}
		shapes.clear();
	}
	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}
	if (npc != NULL) {
		delete npc;
		npc = NULL;
	}
	if (player != NULL) {
		delete player;
		player = NULL;
	}
	if (npcAnim != NULL) {
		delete npcAnim;
		npcAnim = NULL;
	}
}
void Game::InitGame() {
	_shape = new Engine::Shape(Type::triangle, GetRenderer(), basicShader);
	shapes.push_back(new Shape(Type::quad, GetRenderer(), basicShader));
	shapes.push_back(new Shape(Type::triangle, GetRenderer(), basicShader));
	shapes.push_back(new Shape(Type::quad, GetRenderer(), basicShader));

	_sprite = new Engine::Sprite(true, "res/textures/samurai.png", GetRenderer(), textureShader);
	player = new Animation();

	npc = new Engine::Sprite(true, "res/textures/spriteSheet.png", GetRenderer(), textureShader);
	npcAnim = new Animation();

	_sprite->Init();
	npc->Init();
	_shape->Init();

	player->Init(_sprite, glm::ivec2(6,3));
	player->AddAnimation(0, 6, false, 1.25f); //ataque
	player->AddAnimation(6, 11, false, 1.25f); // bloqueo
	player->AddAnimation(12, 14, true, 0.5f); // idle
	player->SetAnimation(2);

	npcAnim->Init(npc, glm::ivec2(7, 1));
	npcAnim->AddAnimation(0, 6, true, 1.0f);
	npcAnim->SetAnimation(0);

	_shape->Scale(100.0f,100.0f,1.0f);
	_sprite->Scale(100.0f, 100.0f, 1.0f);
	npc->Scale(100.0f, 100.0f, 1.0f);
	_shape->transform.position = glm::vec3(200.0f, 300.0f, 0);
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i]) {
			shapes[i]->Init();
			shapes[i]->Scale(100.0f, 100.0f, 0.0f);
		}
	}

	//ahora se pueden mover las cosas estilo unity
	shapes[0]->transform.position = glm::vec3(600.0f, 300.0f, 0.0f);
	shapes[0]->Color(glm::vec3(0.5f,0.0f,1.0f));
	shapes[1]->transform.position = glm::vec3(400.0f, 100.0f, 0.0f);
	shapes[1]->Color(0.7f,0.3f,0.0f);
	shapes[2]->transform.position = glm::vec3(400.0f, 500.0f, 0.0f);
	shapePos = _shape->transform.position;
	_sprite->Color(1.0f, 1.0f, 1.0f);
	_sprite->transform.position = glm::vec3(200,300,1);
	npc->transform.position = glm::vec3(600, 300, 1);


}
void Game::PlayerInputs() {
	if (input.GetKey(KeyCode::W)) {
		_sprite->transform.position.y += 200 * time.GetDeltaTime();
	}
	if (input.GetKey(KeyCode::S)) {
		_sprite->transform.position.y -= 200 * time.GetDeltaTime();
	}
	if (input.GetKey(KeyCode::D)) {
		_sprite->transform.position.x += 200 * time.GetDeltaTime();
	}
	if (input.GetKey(KeyCode::A)) {
		_sprite->transform.position.x -= 200 * time.GetDeltaTime();
	}

	if (input.GetMouseButton(MouseButtons::LEFT_MOUSE_BUTTON)) {
		player->SetAnimation(0);
	}
	if (input.GetMouseButton(MouseButtons::RIGHT_MOUSE_BUTTON)) {
		player->SetAnimation(1);
	}

}
void Game::UpdateGame() {

	PlayerInputs();


	if (!player->GetCurrentAnimation().loop && player->GetCurrentAnimation().hasEnded) {
		player->SetAnimation(2);
	}

	player->UpdateIndex(time);
	//npcAnim->UpdateIndex(time);

	_shape->RotateZ(angle);
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i]){
			shapes[i]->RotateZ(angle);
			shapes[i]->Draw();
		}
	}
	_shape->Draw();
	_sprite->DrawAnimation(player->GetUVs(player->GetCurrentIndex()));
	//npc->DrawAnimation(glm::vec4(0,0,1,1));

}
void Game::UnloadGame() {
	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}
	if (!shapes.empty()) {
		for (int i = 0; i < shapes.size(); i++) {
			if (shapes[i]) {
				delete shapes[i];
				_shape = NULL;
			}
		}
		shapes.clear();
	}
	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}
	if (npc != NULL) {
		delete npc;
		npc = NULL;
	}
	if (player != NULL) {
		delete player;
		player = NULL;
	}
	if (npcAnim != NULL) {
		delete npcAnim;
		npcAnim = NULL;
	}
}