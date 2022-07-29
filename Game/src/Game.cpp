#include "Game.h"

float speed = 100.f;

Game::Game() {

}
Game::~Game() {
	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}

	if (player != NULL) {
		delete player;
		player = NULL;
	}

	if (_tile != NULL) {
		delete _tile;
		_tile = NULL;
	}

	if (map != NULL) {
		delete map;
		map = NULL;
	}
}
void Game::InitGame() {

	_sprite = new Engine::Sprite(true, "res/textures/samurai.png", GetRenderer(), textureShader);
	player = new Animation();

	_tile = new Tile();

	_tile->TestXMLLoad("res/doc.xml");

	//Se necesita pasar bien las dimensiones del tileset para que se hagan los seteos de uv correctamente
	map = new Tilemap(glm::ivec2(16,16), "res/textures/FD_Free_Tiles.png", textureShader, GetRenderer());
	map->LoadMap("res/tilemap/Map1.tmx");

	_sprite->Init();


	player->Init(_sprite, glm::ivec2(6,3));
	//   first frame     Last frame   Loop    anim speed
	player->AddAnimation(0, 6, false, 1.f); //ataque
	player->AddAnimation(6, 11, false, 1.f); // bloqueo
	player->AddAnimation(12, 14, true,  .4f); // idle
	player->SetAnimation(2);


	_sprite->Scale(50.0f, 50.0f, 1.0f);

	//ahora se pueden mover las cosas estilo unity
	_sprite->Color(1.0f, 1.0f, 1.0f);
	_sprite->transform.position = glm::vec3(300,400,1);
}
void Game::PlayerInputs() {
	if (input.GetKey(KeyCode::W)) {
		_sprite->transform.position.y += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::S)) {
		_sprite->transform.position.y -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::D)) {
		_sprite->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::A)) {
		_sprite->transform.position.x -= speed * time.GetDeltaTime();
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
	
	map->Draw();
	
	map->CheckCollisionWithTileMap(_sprite, _sprite->transform.position, speed * time.GetDeltaTime());

	player->UpdateIndex(time);

	_sprite->DrawAnimation(player->GetUVs(player->GetCurrentIndex()));

}
void Game::UnloadGame() {

	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}

	if (player != NULL) {
		delete player;
		player = NULL;
	}

	if (_tile != NULL) {
		delete _tile;
		_tile = NULL;
	}

	if (map != NULL) {
		delete map;
		map = NULL;
	}
}