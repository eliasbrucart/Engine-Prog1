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
		glm::ivec2 _mapDims;
		Shader _shader;
		Renderer* _renderer;
		TextureImporter* _textureImporter;
		CollisionManager* _collisionManager;
		const char* _imagePath;
		Tile* _actualTile = nullptr;

		int _tileWidth;
		int _tileHeight;
		int _mapWidth;
		int _mapHeight;
	public:
		Tilemap();
		Tilemap(glm::ivec2 dimension, const char* imagePath, Shader shader, Renderer* renderer);
		~Tilemap();
		void SetImagePath(const char* path);
		void LoadMap(const char* path);
		void Draw();
		//Agregar metodo para chequeo de colision
	};
}

#endif