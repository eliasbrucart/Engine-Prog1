#ifndef TILEMAP_H
#define TILEMAP_H
#include "export.h"
#include "shader.h"
#include "renderer.h"
#include "collision_manager.h"
#include "texture_importer.h"
#include "tile.h"

#include <vector>
#include <string>
#include <glm.hpp>

namespace Engine {
	class ENGINE_API Tilemap {
	private:
		std::vector<std::vector<std::vector<Tile*>>> _tiles; //primer vector: layer, segundo: filas, tercero: columnas
		std::vector<std::vector<std::vector<int>>> _grid; //primer vector: layer, segundo: filas, tercero: columnas
		glm::ivec2 _mapDims;
		glm::ivec2 _layerDims;
		Shader _shader;
		Renderer* _renderer = nullptr;
		TextureImporter* _textureImporter = nullptr;
		CollisionManager* _collisionManager = nullptr;
		const char* _imagePath;
		Tile* _actualTile = nullptr;

		int _tileWidth;
		int _tileHeight;
		int _mapWidth;
		int _mapHeight;
		int _tilesAmount;

		//Tile* GetTileFromPos(int posX, int posY);
	public:
		Tilemap();
		Tilemap(glm::ivec2 dimension, const char* imagePath, Shader shader, Renderer* renderer);
		~Tilemap();
		void SetImagePath(const char* path);
		void LoadMap(const char* path);
		void LoadMapFromGrid();
		glm::vec4 GetTileFromID(unsigned int id);
		void Draw();
		void CheckCollisionWithTileMap(Entity2D* entity, glm::vec3 entityPosition, float speed);
	};
}

#endif