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

	_layerDims.x = width;
	_layerDims.y = height;

	//buscamos los layers del mapa
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
	_grid.resize(layerCount); //resize del vector a numero de layers encontrados
	for (int l = 0; l < _grid.size(); l++) {
		tinyxml2::XMLText* dataElement = layerElement[l]->FirstChildElement("data")->FirstChild()->ToText();
		if (dataElement == NULL) {
			std::cout << "Error loading tilemap" << std::endl;
			return;
		}

		//en el segundo vector que representa a Y lo llenamos con los datos encontrados dentro del hijo data, 
		//lo mismo para el vector que representa X.
		std::string mapGrid;
		mapGrid = dataElement->Value();
		std::stringstream ss(mapGrid); //creamos un string stream en donde se almaceneran los ids de cada layer
		_grid[l].resize(height);
		for (int y = 0; y < height; y++) {
			_grid[l][y].resize(width);
			for (int x = 0; x < width; x++) {
				std::string value;
				std::getline(ss, value, ',');
				if (!ss.good())
					break;

				int val;
				if (std::stringstream(value) >> val) //string stream usa string buffer para operar con secuencias de caracteres
					_grid[l][y][x] = val;

				_tilesAmount++;
			}
		}
	}

	doc.Clear();
	LoadMapFromGrid();
}

void Tilemap::SetTilesInfo(const char* path) {
	_tilesInfoPath = path;
}

void Tilemap::LoadMapFromGrid() {
	_textureImporter->SetPath(_imagePath); //importamos el .png que contiene las texturas de los tiles
	_textureImporter->LoadImage(_mapWidth, _mapHeight, true); //cargamos la respectiva textura
	int xPos = _tileWidth; //variables necesarias para posicionar cada tile
	std::cout << "tile width: " << _tileWidth << std::endl;
	int yPos = 700;
	float z = 0;
	int actualID = 0;
	_tiles.resize(_grid.size()); //comenzamos a cargar el mapa
	for (int l = 0; l < _grid.size(); l++) {
		xPos = _tileWidth;
		yPos = 700; //cambiar este hardcodeo feo
		_tiles[l].resize(_grid[l].size());
		for (int y = 0; y < _grid[l].size(); y++) {
			_tiles[l][y].resize(_grid[l][y].size());
			for (int x = 0; x < _grid[l][y].size(); x++) {
				Tile* newTile = new Tile(_grid[l][y][x], false, _tileWidth, _tileHeight, _renderer);
				newTile->SetRenderer(_renderer);
				newTile->SetShader(_shader);
				newTile->SetPath(_imagePath); //seteamos la imagen para cada tile
				newTile->Init();
				newTile->Translate(xPos, yPos, z);
				newTile->Scale(_tileWidth, _tileHeight, 1);
				newTile->SetUVs(GetTileFromID(newTile->GetID()));

				//std::cout << "size del vector _tiles" << _tiles[l][x].size() << std::endl;

				if (newTile->GetID() <= 0 && l > 0) { //si el id es menor a 0 o igual y hay layers, borramos el tile
					delete newTile;
					newTile = NULL;
					xPos += _tileWidth + _tileWidth;
				}
				else {
					if (newTile->GetID() > 0 && l > 0) { //si el id es mayor a 0, es decir hay tile y hay layer, seteamos su id
						newTile->SetID(newTile->GetID() - actualID); //se resta por actual id por que al haber mas un layer, tiled los incrementa en uno a los id de los tiles
					}
					newTile->SetIsWalkable(_tilesInfoPath); //seteamos la propiedad is walkable para cada tile
					newTile->SetUVs(GetTileFromID(newTile->GetID()));
					_tiles[l][y][x] = newTile;
					xPos += newTile->transform.scale.x + _tileWidth;
				}
			}
			//al terminar el ciclo en Y restamos el acumulador de posicion en y para la siguiente iteracion
			z += 0.001f;
			yPos -= _tileHeight + _tileHeight;
			xPos = _tileWidth;
			actualID = 1;
		}
	}
	std::cout << "Cantidad de layers: " << _tiles.size() << endl;
}

glm::vec4 Tilemap::GetTileFromID(unsigned int id) {
	int xTile = id % _mapDims.x; // se hace para que cuando el indice sea mayor a la dimension en x, vuelva a ser 0, es decir, se "reinicia" el ciclo en x
	int yTile = id / _mapDims.x;
	yTile = _mapHeight - yTile - 1;
	std::cout << "xTile: " << xTile << std::endl;
	std::cout << "yTile: " << yTile << std::endl;

	//                      x  y   w   h
	glm::vec4 uv = glm::vec4(0, 0, 0, 0);

	uv.x = xTile / static_cast<float>(_mapDims.x); // X
	uv.y = yTile / static_cast<float>(_mapDims.y); // Y
	uv.z = 1.0f / (_mapDims.x); // Ancho / W
	uv.w = 1.0f / (_mapDims.y); // Alto / H

	return uv;
}

//Tile* Tilemap::GetTileFromPos(int posX, int posY) {
//	//hacer
//}

void Tilemap::Draw() {
	if (!_tiles.empty()) {
		for (int i = 0; i < _tiles.size(); i++) { //layer
			for (int j = 0; j < _tiles[i].size(); j++) { //layer filas
				for (int k = 0; k < _tiles[i][j].size(); k++) { //layer columnas
					if (_tiles[i][j][k]) {
						_tiles[i][j][k]->DrawSprite();
						//std::cout << "tile: " << _tiles[i][j][k]->GetID() << " isWalkable " << _tiles[i][j][k]->GetIsWalkable() << std::endl;
					}
				}
			}
		}
	}
}

void Tilemap::CheckCollisionWithTileMap(Entity2D* entity, glm::vec3 entityPosition, float speed) {
	//clculamos la distancia entre la posicion del player con el punto de origen del mapa en X y en Y.
	float distanceWithTilemapX = glm::distance(glm::vec2(entityPosition.x, 0), glm::vec2(0, 0));
	float distanceWithTilemapWidth = glm::distance(glm::vec2(entityPosition.x + entity->transform.scale.x * 0.5f, 0), glm::vec2(0, 0));
	float distanceWithTilemapY = glm::distance(glm::vec2(0, entityPosition.y), glm::vec2(0, 700));
	float distanceeWithTilemapHeight = glm::distance(glm::vec2(0, entityPosition.y - entity->transform.scale.y * 0.5f), glm::vec2(0, 700));

	//conseguir los indices en base a la distancia obtenida y dividiendo los valores en X y en Y por el ancho y alto de cada tile.
	float indexInX = distanceWithTilemapX / _tileWidth * 0.5f;
	float indexInY = distanceWithTilemapY / _tileHeight * 0.5f;
	float indexInWidth = distanceWithTilemapWidth / _tileWidth * 0.5f;
	float indexInHeight = distanceeWithTilemapHeight / _tileHeight * 0.5f;

	//std::cout << "indexInX: " << indexInX << std::endl;
	//std::cout << "indexInY: " << indexInY << std::endl;
	//std::cout << "indexInWidth: " << indexInWidth << std::endl;
	//std::cout << "indexInHeight: " << indexInHeight << std::endl;

	//conseguimos los tiles vecinos en base a los indices obtenidos
	int rightTile = static_cast<int>(indexInWidth) + 1;
	int leftTile = static_cast<int>(indexInX) - 1;
	int topTile = static_cast<int>(indexInY) - 1;
	int bottomTile = static_cast<int>(indexInHeight) + 1;

	std::cout << "rightTile: " << rightTile << std::endl;
	std::cout << "leftTile: " << leftTile << std::endl;
	std::cout << "topTile: " << topTile << std::endl;
	std::cout << "bottomTile: " << bottomTile << std::endl;

	//recorremos los tiles vecinos, obtenidos previamente y chequeamos la colision solo con los vecinos.
	for (int i = leftTile; i <= rightTile; i++) {
		for (int j = topTile; j <= bottomTile; j++) {
			for (int l = 0; l < _grid.size(); l++) {
									//Le restamos uno ya que en la carga del mapa, el conteo comienza desde 0.
				if (i >= 0 && i <= _layerDims.x -1 && j >= 0 && j <= _layerDims.y -1 && l >= 0) {
					Tile* t = _tiles[l][j][i];
					if (t != NULL && !t->GetIsWalkable()) {
						_collisionManager->CheckCollision(entity, t, speed);
						//std::cout << "ta colisionando con el tile: " << t->GetID() << std::endl;
					}
				}
			}
		}
	}
}