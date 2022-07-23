#ifndef TILE_H
#define TILE_H
#include "export.h"

namespace Engine {
	class ENGINE_API Tile {
	private:
		unsigned int _id;
		bool _isWalkable;
		int _width;
		int _height;
	public:
		Tile();
		Tile(unsigned int id, bool isWalkable, int width, int height);
		~Tile();
		void TestXMLLoad(const char* path);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetIsWalkable();
		int GetWidth();
		int GetHeight();
		bool GetIsWalkable();
	};
}

#endif