#ifndef TILE_H
#define TILE_H
#include "export.h"
#include "renderer.h"

namespace Engine {
	class ENGINE_API Tile {
	private:
		unsigned int _id;
		bool _isWalkable;
		int _width;
		int _height;
		Renderer* _renderer;
	public:
		Tile();
		Tile(unsigned int id, bool isWalkable, int width, int height, Renderer* renderer);
		~Tile();
		void TestXMLLoad(const char* path);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetIsWalkable();
		int GetWidth();
		int GetHeight();
		bool GetIsWalkable();
		void Draw();
	};
}

#endif