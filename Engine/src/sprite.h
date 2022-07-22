#ifndef SPRITE_H
#define SPRITE_H
#include"shape.h"
#include"export.h"
#include"texture_importer.h"
#include"renderer.h"

namespace Engine {
	class Animation;
	class Time;

	struct ENGINE_API UVs {
		float u;
		float v;
	};

	class ENGINE_API Sprite : public Entity2D {
	private:
		int _width=0;
		int _height=0;
		bool _transparency;
		Renderer* _renderer;
		TextureImporter* _texImporter;
		UVs uv[4];
		unsigned int _texture = 0;

		unsigned int _vao = 0;
		unsigned int _vbo = 0;
		unsigned int _ebo = 0;

		float _vertices[32] = {
	        	1.0f,  1.0f, 0.0f,  1.0f,1.0f,1.0f,  1, 1,
	        	1.0f, -1.0f, 0.0f,  1.0f,1.0f,1.0f,  1, 0,
	           -1.0f, -1.0f, 0.0f,  1.0f,1.0f,1.0f,  0, 0,
	           -1.0f,  1.0f, 0.0f,  1.0f,1.0f,1.0f,  0, 1
			};

		unsigned int _quadIndices[6] = {
			0,1,3,
			1,2,3
		};
		Shader shader;

		void GenerateVAO();
		void BindVAO();
		void BindVBO();
		void BindEBO();
		void UnbindBuffers();
		void DeleteBuffer();
		void BindBuffers();
		void BindTexture();
		void BlendSprite();
		void UnBlendSprite();
		void LoadSprite();
		void LoadSprite(const char* path);
		void SetWidth(int width);
		int GetWidth();
		void SetHeight(int height);
		int GetHeight();

	public:
		Sprite();
		Sprite(bool transparency, Renderer* renderer, Shader shader);
		Sprite(bool transparency, const char* path,  Renderer* renderer, Shader shader);
		~Sprite();
		void Init();
		void Init(unsigned int texture);
		void Color(float r, float g, float b);
		void Color(glm::vec3 color);
		void SetUVs(glm::vec4 uvRect);
		void SetUVs(float sheetHeight, float sheetWidth, float spriteHeight, float spriteWidth, int x, int y);
		void UpdateUVs();
		void DrawSprite();
		void DrawFromUVs(glm::vec4 uv);
		void DrawAnimation(glm::vec4 uv);
		void SetRenderer(Renderer* renderer);
		void SetShader(Shader shader);
		Renderer* GetRenderer();
		void SetPath(const char* path);
		const char* GetPath();
		void SetTransparency(bool value);
	};
}

#endif