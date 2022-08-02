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
		int _posX;
		int _posY;
		Renderer* _renderer;
	public:
		Tile();
		Tile(unsigned int id, bool isWalkable);
		Tile(unsigned int id, bool isWalkable, int width, int height, Renderer* renderer);
		Tile(unsigned int id, bool isWalkable, int width, int height, int posX, int posY, Renderer* renderer);
		~Tile();
		void SetID(unsigned int id);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetIsWalkable(const char* path);
		void SetPosX(int posX);
		void SetPosY(int posY);
		unsigned int GetID();
		int GetWidth();
		int GetHeight();
		bool GetIsWalkable();
		int GetPosX();
		int GetPosY();
		//int Tile* GetTileFromPos(int posX, int posY);
		void Draw();
	};
}

#endif