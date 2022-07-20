#include "entity2D.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "ext/scalar_constants.hpp"

using namespace Engine;

void Engine::Entity2D::UpdateMatrices() {
	model.translate = glm::translate(glm::mat4(1.0f), transform.position);
	model.scale = glm::scale(glm::mat4(1.0f), transform.scale);

	UpdateModel();
}

void Entity2D::UpdateModel() {
	model.trs = model.translate * model.rotation.x * model.rotation.y * model.rotation.z * model.scale;
}

Entity2D::Entity2D() {
	model.translate = glm::mat4(1.0);
	model.rotation.x = glm::mat4(1.0);
	model.rotation.y = glm::mat4(1.0);
	model.rotation.z = glm::mat4(1.0);
	model.scale = glm::mat4(1.0);

	Translate(1.0f, 1.0f, 1.0f);
	RotateX(0.0f);
	RotateY(0.0f);
	RotateZ(0.0f);
	Scale(1.0f, 1.0f, 1.0f);
}

Entity2D::~Entity2D() {

}

void Engine::Entity2D::RotateX(float angle) {
	transform.rotation.x = angle;
	glm::vec3 axis = glm::vec3(1.0);
	axis[0] = 1.0f;
	axis[1] = 0.0f;
	axis[2] = 0.0f;
	model.rotation.x = glm::rotate(glm::mat4(1.0), angle, axis);
	UpdateModel();
}

void Engine::Entity2D::RotateY(float angle) {
	transform.rotation.x = angle;
	glm::vec3 axis = glm::vec3(1.0);
	axis[0] = 0.0f;
	axis[1] = 1.0f;
	axis[2] = 0.0f;
	model.rotation.y = glm::rotate(glm::mat4(1.0), angle, axis);
	UpdateModel();
}

void Engine::Entity2D::RotateZ(float angle) {
	transform.rotation.x = angle;
	glm::vec3 axis = glm::vec3(1.0);
	axis[0] = 0.0f;
	axis[1] = 0.0f;
	axis[2] = 1.0f;
	model.rotation.z = glm::rotate(glm::mat4(1.0), angle, axis);
	UpdateModel();
}



void Entity2D::Translate(float x, float y, float z) {
	transform.position.x = x;
	transform.position.y = y;
	transform.position.z = z;

	model.translate = glm::translate(glm::mat4(1.0), transform.position);
	UpdateModel();
}

glm::vec2 Entity2D::Lerp(glm::vec2 a, glm::vec2 b, float t){
	glm::vec2 auxVec = glm::vec2(1.0);

	if (t < 1)
		auxVec = glm::vec2((b - a) * t + a);
	else
		t = 1;
	return auxVec;

}


void Entity2D::Scale(float x, float y, float z) {
	transform.scale.x = x;
	transform.scale.y = y;
	transform.scale.z = z;

	model.scale = glm::scale(glm::mat4(1.0), transform.scale);
	UpdateModel();
}

glm::mat4 Entity2D::GetModel() {
	return model.trs;
}


