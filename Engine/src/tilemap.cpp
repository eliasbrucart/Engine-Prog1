#include "tilemap.h"

using namespace Engine;

Tilemap::Tilemap(glm::ivec2 dimension, const char* imagePath, Shader shader, Renderer* renderer) {
	_mapDims = dimension;
	_imagePath = imagePath;
	_shader = shader;
	_renderer = renderer;
	_textureImporter = new TextureImporter();
	_collisionManager = new CollisionManager();
}

Tilemap::Tilemap() {
	_mapDims = glm::ivec2(0, 0);
	_imagePath = "";
	_renderer = nullptr;
	_textureImporter = nullptr;
	_collisionManager = nullptr;
}

Tilemap::~Tilemap() {

}

void Tilemap::SetImagePath(const char* path) {
	_imagePath = path;
}

void Tilemap::LoadMap(const char* path) {
	//Aca hacemos las carga del mapa a travez de tinyxml
}

void Tilemap::Draw() {
	//Llamamos al draw de la clase tile para dibujar cada uno de los tiles
}