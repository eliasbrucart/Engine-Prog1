#include "tilemap.h"
#include "xml_lib/tinyxml2.h"

using namespace tinyxml2;
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
	tinyxml2::XMLDocument doc;

	doc.LoadFile(path);

	//Creamos los punteros para obtener los elementos del archivo xml
	tinyxml2::XMLElement* p_root_element = doc.RootElement();
}

void Tilemap::Draw() {
	//Llamamos al draw de la clase tile para dibujar cada uno de los tiles
}