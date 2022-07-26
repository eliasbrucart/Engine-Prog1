#include "tilemap.h"
#include "xml_lib/tinyxml2.h"
#include <sstream>

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
	if (!_grid.empty())
		_grid.clear();

	if (!_tiles.empty()) {
		for (int i = 0; i < _tiles.size(); i++) {
			for (int j = 0; j < _tiles[i].size(); j++) {
				for (int k = 0; k < _tiles[i][j].size(); k++) {
					if (_tiles[i][j][k]) {
						delete _tiles[i][j][k];
						_tiles[i][j][k] = NULL;
					}
				}
			}
		}
		_tiles.clear();
	}

	if (_textureImporter != NULL) {
		delete _textureImporter;
		_textureImporter = NULL;
	}

	if (_collisionManager != NULL) {
		delete _collisionManager;
		_collisionManager = NULL;
	}
}

void Tilemap::SetImagePath(const char* path) {
	_imagePath = path;
}

void Tilemap::LoadMap(const char* path) {
	//Aca hacemos las carga del mapa a travez de tinyxml
	tinyxml2::XMLDocument doc;

	doc.LoadFile(path);

	//Creamos los punteros para obtener los elementos del archivo xml
	tinyxml2::XMLElement* p_root_element = doc.FirstChildElement("map");

	if (p_root_element == NULL) {
		std::cout << "Error loading tilemap" << std::endl;
		return;
	}
	
	//Almacenamos el ancho y alto del mapa como el ancho y alto de cada tile
	int width = p_root_element->IntAttribute("width");
	int height = p_root_element->IntAttribute("height");
	_tileWidth = p_root_element->IntAttribute("tilewidth");
	_tileHeight = p_root_element->IntAttribute("tileheight");

	int layerCount = 0;
	std::vector<tinyxml2::XMLElement*> layerElement;
	for (tinyxml2::XMLElement* childElement = p_root_element->FirstChildElement(); childElement != NULL; childElement = childElement->NextSiblingElement()) {
		string childName = childElement->Name();
		string layer = "layer";
		if (childElement != NULL && childName == layer) {
			layerCount++;
			layerElement.push_back(childElement);
		}
	
	}
	std::cout << "cantidad de layers cargados desde archivo: " << layerCount << std::endl;
	_grid.resize(layerCount);
	for (int l = 0; l < _grid.size(); l++) {
		tinyxml2::XMLText* dataElement = layerElement[l]->FirstChildElement("data")->FirstChild()->ToText();
		if (dataElement == NULL) {
			std::cout << "Error loading tilemap" << std::endl;
			return;
		}

		std::string mapGrid;
		mapGrid = dataElement->Value();
		std::stringstream ss(mapGrid);
		_grid[l].resize(height);
		for (int y = 0; y < height; y++) {
			_grid[l][y].resize(width);
			for (int x = 0; x < width; x++) {
				std::string value;
				std::getline(ss, value, ',');
				if (!ss.good())
					break;

				int val;
				if (std::stringstream(value) >> val)
					_grid[l][y][x] = val;

				_tilesAmount++;
			}
		}
	}

	doc.Clear();
	LoadMapFromGrid();
}

void Tilemap::LoadMapFromGrid() {
	_textureImporter->SetPath(_imagePath);
	_textureImporter->LoadImage(_mapWidth, _mapHeight, true);
	int xPos = _tileWidth; //variables necesarias para posicionar cada tile
	std::cout << "tile width: " << _tileWidth << std::endl;
	int yPos = 700;
	float z = 0;
	int actualID = 0;
	_tiles.resize(_grid.size());
	for (int l = 0; l < _grid.size(); l++) {
		xPos = _tileWidth;
		yPos = 700; //cambiar este hardcodeo feo
		_tiles[l].resize(_grid[l].size());
		for (int y = 0; y < _grid[l].size(); y++) {
			_tiles[l][y].resize(_grid[l][y].size());
			for(int x = 0; x < _grid[l][y].size(); x++){
				Tile* newTile = new Tile(_grid[l][y][x], false, _tileWidth, _tileHeight, _renderer);
				newTile->SetRenderer(_renderer);
				newTile->SetShader(_shader);
				newTile->SetPath(_imagePath);
				newTile->Init();
				newTile->Translate(xPos, yPos, z);
				newTile->Scale(_tileWidth, _tileHeight, 1);

				std::cout << "size del vector _tiles" << _tiles[l][x].size() << std::endl;
				
				if (newTile->GetID() <= 0 && l > 0) {
					delete newTile;
					newTile = NULL;
					xPos += _tileWidth + _tileWidth;
				}
				else {
					if (newTile->GetID() > 0 && l > 0) {
						newTile->SetID(newTile->GetID() - actualID);
					}
					newTile->SetIsWalkable("res/tilemap/Terrain.tsx"); //Por el momento no hace nada
					newTile->SetUVs(GetTileFromID(newTile->GetID()));
					_tiles[l][y][x] = newTile;
					xPos += newTile->transform.scale.x + _tileWidth;
				}
			}

			z += 0.001f;
			yPos -= _tileHeight + _tileHeight;
			xPos = _tileWidth;
		}
		actualID = 1;
	}
	std::cout << "Cantidad de layers: " << _tiles.size() << endl;
}

glm::vec4 Tilemap::GetTileFromID(unsigned int id) {
	int xTile = id % _mapDims.x; // se hace para que cuando el indice sea mayor a la dimension en x, vuelva a ser 0, es decir, se "reinicia" el ciclo en x
	int yTile = id / _mapDims.x;
	yTile = _mapHeight - yTile - 1;
	//                      x  y   w   h
	glm::vec4 uv = glm::vec4(0, 0, 0, 0);

	uv.x = xTile / static_cast<float>(_mapDims.x); // X
	uv.y = yTile / static_cast<float>(_mapDims.y); // Y
	uv.z = 1.0f / (_mapDims.x); // Ancho / W
	uv.w = 1.0f / (_mapDims.y); // Alto / H

	return uv;
}

void Tilemap::Draw() {
	//Llamamos al draw de la clase tile para dibujar cada uno de los tiles
	if (!_tiles.empty()) {
		for (int i = 0; i < _tiles.size(); i++) { //layer
			for (int j = 0; j < _tiles[i].size(); j++) { //layer filas
				for (int k = 0; k < _tiles[i][j].size(); k++) { //layer columnas
					if (_tiles[i][j][k])
						_tiles[i][j][k]->DrawSprite();
				}
			}
		}
	}
}