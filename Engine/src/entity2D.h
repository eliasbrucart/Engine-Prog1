#ifndef ENTITY2D_H
#define ENTITY2D_H
#include "export.h"
#include "mat4x4.hpp"
#include "vec3.hpp"

namespace Engine {

	struct ENGINE_API Rotation {
		glm::mat4 x;
		glm::mat4 y;
		glm::mat4 z;
	};

	struct ENGINE_API Transform {
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};

	struct ENGINE_API Model {
		glm::mat4 translate;
		Rotation rotation;
		glm::mat4 scale;
		glm::mat4 trs;
	};

	class ENGINE_API Entity2D {
	private:
	protected:
		Model model;
		void UpdateMatrices();
		void UpdateModel();
	public:
		Transform transform;
		Entity2D();
		~Entity2D();
		void RotateX(float angle);
		void RotateY(float angle);
		void RotateZ(float angle);
		void Translate(float x, float y, float z);
		glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float t);
		void Scale(float x, float y, float z);
		glm::mat4 GetModel();
	};

}

#endif // !ENTITY2D_H

