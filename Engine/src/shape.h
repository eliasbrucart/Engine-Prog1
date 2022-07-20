#ifndef SHAPE_H
#define SHAPE_H
#include "export.h"
#include "entity2D.h"
#include "shader.h"
#include "renderer.h"
namespace Engine {

	enum class ENGINE_API Type
	{
		triangle, quad
	};

	class ENGINE_API Shape : public Entity2D{
	private:
		unsigned int _vao = 0;
		unsigned int _vbo = 0;
		unsigned int _ebo = 0;

		float _triVertices[18] = {
			-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f,
			 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		unsigned int _triIndices[3] = {
			0,1,2
		};
		float _quadVertices[24] = {
			0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
		   -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
	       -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f   // top left 
		};
		unsigned int _quadIndices[6] = {
			0,1,3,
			1,2,3
		};

		Type _type;
		Renderer* _renderer;
		Shader _shader;

		void GenerateVAO();
		void BindVAO();
		void BindVBO(float* vertices, int AmmountOfVertices);
		void BindEBO(unsigned int* indices, int AmmountOfIndices);
		void UnbindBuffers();
		void DeleteBuffer();
	public:
		Shape();
		Shape(Type type, Renderer* renderer, Shader shader);
		~Shape();
		void SetRenderer(Renderer* renderer);
		void SetShader(Shader shader);
		void Init();
		void Color(float r, float g, float b);
		void Color(glm::vec3 color);
		void Draw();

	};

}
#endif // !SHAPE_H

