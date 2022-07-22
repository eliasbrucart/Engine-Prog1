#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "renderer.h"
#include "shader.h"

#include <iostream>

using namespace Engine;

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

bool Renderer::InitializeGlew() {
	glewExperimental = GL_TRUE;
	glewInit();
	if (glewInit() != GLEW_OK) {
		std::cout << "Error in GLEW INIT" << std::endl;
		std::cout << glewGetErrorString(glewInit()) << std::endl;
		return false;
	}
	return true;
}

void Renderer::BeginFrame(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::EndFrame(GLFWwindow* window) {
	glfwSwapBuffers(window);
	glfwPollEvents();
}
void Renderer::GenerateVAO(unsigned int& vao) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}
void Renderer::BindVAO(unsigned int& vao) {
	glBindVertexArray(vao);
}
void Renderer::BindVBO(unsigned int& vbo, float* vertices, int verticesAmmount) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * verticesAmmount, vertices, GL_STATIC_DRAW);
}
void Renderer::BindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmmount) {
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * indicesAmmount, indices, GL_STATIC_DRAW);
}
void Engine::Renderer::UpdateBuffers(unsigned int& vbo, float* vertices, int verticesAmmount)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * verticesAmmount, vertices, GL_STATIC_DRAW);
}
void Renderer::UnbindBuffers() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}
void Renderer::DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo) {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void Renderer::CreateAtribPointers(unsigned int shaderAttribIndex, int dataAmmount, int dataSize, int dataPosition) {
	glVertexAttribPointer(shaderAttribIndex, dataAmmount, GL_FLOAT, GL_FALSE, sizeof(float) * dataSize, (void*)(sizeof(float) * dataPosition));
	glEnableVertexAttribArray(shaderAttribIndex);
}

void Renderer::SetTexAttribPointer(unsigned int shaderID) {
	GLuint posAttrib = glGetAttribLocation(shaderID, "aPos");
	GLuint colorAttrib = glGetAttribLocation(shaderID, "aColor"); // no daba el valor correcto porque no usaba la variable en el main
	GLuint texAttrib = glGetAttribLocation(shaderID, "aTexCoord");
	glUniform1i((glGetUniformLocation(shaderID, "mainTexture")), 0);
	CreateAtribPointers(posAttrib, 3, 8, 0);
	CreateAtribPointers(colorAttrib, 3, 8, 3);
	CreateAtribPointers(texAttrib, 2, 8, 6);
}

void Renderer::Draw(Shader& shader, glm::mat4 model, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount, unsigned int* indices, int indicesAmmount){
	BindVAO(vao);
	UpdateBuffers(vbo, vertices, verticesAmount);
	shader.SetVertexAttributes("position",6); //especificamos como leer los datos del vertice y se lo pasamos al shader
	shader.SetColorAttributes("color",6);
	shader.Use(model);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	UnbindBuffers();
}
void Renderer::DrawSprite(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount, unsigned int* indices, int indicesAmmount, glm::mat4 model) {
	BindVAO(vao);
	UpdateBuffers(vbo,vertices, verticesAmount);
	SetTexAttribPointer(shader.GetID());
	shader.Use(model);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	UnbindBuffers();
}

void Renderer::DrawCamera(Shader& shader, glm::mat4 model, glm::mat4 view) {
	//unsigned int projLoc = glGetUniformLocation(shader.GetID(), "projection");
	shader.Use();

	unsigned int transformLoc = glGetUniformLocation(shader.GetID(), "model");
	unsigned int viewLoc = glGetUniformLocation(shader.GetID(), "view");

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
}


