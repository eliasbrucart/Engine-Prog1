#include "tile.h"
#include "xml_lib/tinyxml2.h"

//Agregar el namespace de la libreria para poder hacer uso de sus funciones
using namespace tinyxml2;
using namespace Engine;

Tile::Tile() {
	_id = 0;
	_isWalkable = false;
	_width = 0;
	_height = 0;
}

Tile::Tile(unsigned int id, bool isWalkable, int width, int height) {
	_id = id;
	_isWalkable = isWalkable;
	_width = width;
	_height = height;
}

Tile::~Tile() {

}

void Tile::SetWidth(int width) {
	_width = width;
}

void Tile::SetHeight(int height) {
	_height = height;
}

//Metodo para lo ultimo, ver que parametros le pasamos para setear la variable
void Tile::SetIsWalkable() {

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