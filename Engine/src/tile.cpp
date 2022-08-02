#include "tile.h"
#include "xml_lib/tinyxml2.h"
#include <vector>
#include <iostream>

//Agregar el namespace de la libreria para poder hacer uso de sus funciones
using namespace tinyxml2;
using namespace Engine;

Tile::Tile() : Sprite() {
	_id = 0;
	_isWalkable = false;
	_width = 0;
	_height = 0;
}

Tile::Tile(unsigned int id, bool isWalkable) : Sprite(){
	_id = id;
	_isWalkable = isWalkable;
}

Tile::Tile(unsigned int id, bool isWalkable, int width, int height, Renderer* renderer) : Sprite() {
	_id = id;
	_isWalkable = isWalkable;
	_width = width;
	_height = height;
	_renderer = renderer;
}

Tile::Tile(unsigned int id, bool isWalkable, int width, int height, int posX, int posY, Renderer* renderer) : Sprite() {
	_id = id;
	_isWalkable = isWalkable;
	_width = width;
	_height = height;
	_posX = posX;
	_posY = posY;
	_renderer = renderer;
}

Tile::~Tile() {

}

void Tile::SetID(unsigned int id) {
	_id = id;
}

void Tile::SetWidth(int width) {
	_width = width;
}

void Tile::SetHeight(int height) {
	_height = height;
}

//Metodo para lo ultimo, ver que parametros le pasamos para setear la variable
void Tile::SetIsWalkable(const char* path) {
	tinyxml2::XMLDocument doc;

	doc.LoadFile(path);

	tinyxml2::XMLElement* tileset = doc.FirstChildElement("tileset");
	if (tileset) {
		for (tinyxml2::XMLNode* tile = tileset->FirstChildElement(); tile != NULL; tile = tile->NextSiblingElement()) {
			if (tile->ToElement() && tile->ToElement()->IntAttribute("id") && tile->ToElement()->IntAttribute("id") == _id) {
				tinyxml2::XMLElement* properties = tile->FirstChildElement("properties");
				if (properties != NULL) {
					tinyxml2::XMLElement* propertyElement = properties->FirstChildElement("property");
					if (propertyElement != NULL)
						_isWalkable = propertyElement->BoolAttribute("value");
				}
			}
		}
	}
	doc.Clear();
}

void Tile::SetPosX(int posX) {
	_posX = posX;
}

void Tile::SetPosY(int posY) {
	_posY = posY;
}

unsigned int Tile::GetID() {
	return _id;
}

int Tile::GetWidth() {
	return _width;
}

int Tile::GetHeight() {
	return _height;
}

bool Tile::GetIsWalkable() {
	return _isWalkable;
}

int Tile::GetPosX() {
	return _posX;
}

int Tile::GetPosY() {
	return _posY;
}

void Tile::Draw() {
	//_renderer->DrawSprite();
}