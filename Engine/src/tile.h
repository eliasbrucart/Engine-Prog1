#ifndef TILE_H
#define TILE_H
#include "export.h"
#include "renderer.h"
#include "sprite.h"

namespace Engine {
	class ENGINE_API Tile : public Sprite {
	private:
		unsigned int _id;
		bool _isWalkable;
		int _width;
		int _height;
		Renderer* _renderer;
	public:
		Tile();
		Tile(unsigned int id, bool isWalkable);
		Tile(unsigned int id, bool isWalkable, int width, int height, Renderer* renderer);
		~Tile();
		void SetID(unsigned int id);
		void TestXMLLoad(const char* path);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetIsWalkable(const char* path);
		unsigned int GetID();
		int GetWidth();
		int GetHeight();
		bool GetIsWalkable();
		void Draw();
	};
}

#endif