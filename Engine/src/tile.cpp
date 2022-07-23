#include "tile.h"
#include "xml_lib/tinyxml2.h"
#include <vector>
#include <iostream>

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

void Tile::TestXMLLoad(const char* path) {
	tinyxml2::XMLDocument doc;

	doc.LoadFile(path);

	std::vector<const char*> elems = { "title", "description", "date", "time", "tag" };

	tinyxml2::XMLElement* p_root_element = doc.RootElement();
	tinyxml2::XMLElement* p_article = p_root_element->FirstChildElement("article");

	while (p_article) {
		for (std::size_t i{}; i < elems.size(); i++) {
			tinyxml2::XMLElement* ptr = p_article->FirstChildElement(elems[i]);
			std::cout << elems[i] << ": " << ptr->GetText() << '\n';
			std::cout << (i == elems.size() - 1 ? "\n" : "");
		}
		p_article = p_article->NextSiblingElement("article");
	}
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