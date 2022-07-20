#ifndef CAMERA_H
#define CAMERA_H
#include "export.h"
#include "renderer.h"
#include "shader.h"
#include "entity2D.h"
namespace Engine {

	enum class ENGINE_API ProjectionType {
		orthographic, perspective
	};

	class ENGINE_API Camera : public Entity2D{
	private:
		Renderer* _renderer;
		ProjectionType _type;
		glm::mat4 _view;
		glm::mat4 _projection;
	public:
		Camera(Renderer* renderer, ProjectionType type);
		~Camera();
		void SetView(glm::vec3 direction, glm::vec3 up);
		void SetProjection(ProjectionType type);
		void Init(Shader& shader);
		glm::mat4 GetView();
		glm::mat4 GetProjection();
		glm::mat4 GetMVP();
		ProjectionType GetProjectionType();
		void Draw(Shader& shader);
	};

}

#endif // !CAMERA_H

