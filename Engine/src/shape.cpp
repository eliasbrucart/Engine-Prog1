#include "shape.h"
#include "renderer.h"


using namespace Engine;

Shape::Shape() : Entity2D() {
	_type = Type::triangle;
	_renderer = NULL;
}

Shape::Shape(Type type, Renderer* renderer, Shader shader) : Entity2D() {
	_type = type;
	_renderer = renderer;
	_shader = shader;
}
Shape::~Shape() {
	UnbindBuffers();
	DeleteBuffer();
}

void Shape::SetShader(Shader shader) {
	_shader = shader;
}

void Shape::GenerateVAO() {
	_renderer->GenerateVAO(_vao);
}

void Shape::BindVAO() {
	_renderer->BindVAO(_vao);
}

void Shape::BindVBO(float* vertices, int verticesAmmount) {
	_renderer->BindVBO(_vbo, vertices, verticesAmmount);
}

void Shape::BindEBO(unsigned int* indices, int indicesAmmount) {
	_renderer->BindEBO(_ebo, indices, indicesAmmount);
}

void Shape::Init() {
	GenerateVAO();
	BindVAO();
	switch (_type)
	{
	case Engine::Type::triangle:
		BindVBO(_triVertices,18);
		BindEBO(_triIndices,3);
		break;
	case Engine::Type::quad:
		BindVBO(_quadVertices, 24);
		BindEBO(_quadIndices, 6);
		break;
	}
	_shader.SetVertexAttributes("position", 6);
	_shader.SetColorAttributes("color", 6);
}

void Shape::Color(float r, float g, float b) {
	switch (_type)
	{
	case Engine::Type::triangle:
		_triVertices[3] = r;  _triVertices[4] = g;  _triVertices[5] = b;
		_triVertices[9] = r; _triVertices[10] = g; _triVertices[11] = b;
		_triVertices[15] = r; _triVertices[16] = g; _triVertices[17] = b;
		break;
	case Engine::Type::quad:
		_quadVertices[3] = r;  _quadVertices[4] = g;  _quadVertices[5] = b;
		_quadVertices[9] = r; _quadVertices[10] = g; _quadVertices[11] = b;
		_quadVertices[15] = r; _quadVertices[16] = g; _quadVertices[17] = b;
		_quadVertices[21] = r; _quadVertices[22] = g; _quadVertices[23] = b;
		break;
	}
}

void Shape::SetRenderer(Renderer* renderer){
	_renderer = renderer;
}

void Shape::Color(glm::vec3 color) {
	switch (_type)
	{
	case Engine::Type::triangle:
		_triVertices[3] = color.x;  _triVertices[4] = color.y;  _triVertices[5] = color.z;
		_triVertices[9] = color.x; _triVertices[10] = color.y; _triVertices[11] = color.z;
		_triVertices[15] = color.x; _triVertices[16] = color.y; _triVertices[17] = color.z;
		break;
	case Engine::Type::quad:
		_quadVertices[3] = color.x;  _quadVertices[4] = color.y;  _quadVertices[5] = color.z;
		_quadVertices[9] = color.x; _quadVertices[10] = color.y; _quadVertices[11] = color.z;
		_quadVertices[15] = color.x; _quadVertices[16] = color.y; _quadVertices[17] = color.z;
		_quadVertices[21] = color.x; _quadVertices[22] = color.y; _quadVertices[23] = color.z;
		break;
	}
}

void Shape::Draw() {
	UpdateMatrices();
	switch (_type)
	{
	case Engine::Type::triangle:
		_renderer->Draw(_shader, GetModel(), _vao, _vbo, _triVertices, 18, _triIndices, 3);
		break;
	case Engine::Type::quad:
		_renderer->Draw(_shader, GetModel(), _vao, _vbo, _quadVertices, 24, _quadIndices, 6);
		break;
	}
}

void Shape::UnbindBuffers() {
	_renderer->UnbindBuffers();
}

void Shape::DeleteBuffer() {
	_renderer->DeleteBuffers(_vao, _vbo, _ebo);
}