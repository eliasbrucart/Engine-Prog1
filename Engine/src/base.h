#ifndef BASE_H
#define BASE_H

#include "export.h"
#include "renderer.h"
#include "window.h"
#include "shader.h"
#include "shape.h"
#include "sprite.h"
#include "camera.h"
#include "input.h"
#include "animation.h"
#include "time_manager.h"
#include "collision_manager.h"
#include "tile.h"
#include "tilemap.h"
#include "xml_lib/tinyxml2.h"

namespace Engine {
	class ENGINE_API Base {
	private:
		Renderer* _renderer;
		Window* _window;
	protected:
		Camera* _camera;
		Shader basicShader;
		Shader textureShader;
		Renderer* GetRenderer();
		Window* GetWindow();
		CollisionManager* collisionmanager;

		Time time;
		Input input;
		int Init();
		void Update();
		void Unload();
	public:
		Base();
		~Base();

		void Execute();

		virtual void InitGame() = 0;
		virtual void UpdateGame() = 0;
		virtual void UnloadGame() = 0;

	};
}

#endif // !BASE_H
