#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "shader.h"

#include <fstream>
#include <sstream> // para leer y escribir strings en archivos



using namespace Engine;

Shader::Shader() {
	_id = 0;
}
Shader::~Shader() {

}
void Shader::Create(const char* vertexPath, const char* fragmentPath) {
	// ------------------Find Shader-----------------
	std::string vertex;
	std::string fragment;

	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	std::stringstream vertexBuffer;
	std::stringstream fragmentBuffer;

	vertexFile.open(vertexPath);
	if (vertexFile.is_open()) {
		vertexBuffer << vertexFile.rdbuf();
		vertexFile.close();
	}
	else {
		std::cout << "Couldn't open vertex file" << std::endl;
	}

	fragmentFile.open(fragmentPath);
	if (fragmentFile.is_open()) {
		fragmentBuffer << fragmentFile.rdbuf();
		fragmentFile.close();
	}
	else {
		std::cout << "Couldn't open fragment file" << std::endl;
	}

	vertex = vertexBuffer.str();
	fragment = fragmentBuffer.str();

	// -----------Compile------------------

	_id = glCreateProgram();
	unsigned int vertexID = Compile(GL_VERTEX_SHADER, vertex);
	unsigned int fragmentID = Compile(GL_FRAGMENT_SHADER, fragment);
	glAttachShader(_id, vertexID);
	glAttachShader(_id, fragmentID);

	glLinkProgram(_id);
	glValidateProgram(_id);

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}
unsigned int Shader::Compile(unsigned int type, std::string& source) {
	unsigned int shaderID = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shaderID, 1, &src, nullptr);
	glCompileShader(shaderID);

	int result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(shaderID, length, &length, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(shaderID);
		return 0;
	}
	return shaderID;
}
void Shader::CreateAttribPointer(unsigned int shaderAttribIndex, int dataAmmount, int dataSize, int dataPosition){
	glVertexAttribPointer(shaderAttribIndex, dataAmmount, GL_FLOAT, GL_FALSE, sizeof(float) * dataSize, (void*)(sizeof(float) * dataPosition));
	glEnableVertexAttribArray(shaderAttribIndex);
}
void Shader::Use() {
	glUseProgram(_id);
}
void Shader::Use(glm::mat4 model) {
	unsigned int matrixLoc = glGetUniformLocation(_id, "model");
	glUseProgram(_id);
	glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, glm::value_ptr(model));
}
void Shader::SetVertexAttributes(const char* name, int vertexSize) {
	unsigned int attribute = glGetAttribLocation(_id, name);
	CreateAttribPointer(attribute, 3, vertexSize, 0);
}
void Shader::SetColorAttributes(const char* name, int vertexSize) {
	unsigned int attribute = glGetAttribLocation(_id, name);
	CreateAttribPointer(attribute, 3, vertexSize, 3);
}
void Shader::SetTextureAttributes(const char* name, int vertexSize) {
	unsigned int attribute = glGetAttribLocation(_id, name);
	CreateAttribPointer(attribute, 2, vertexSize, 6);
}
unsigned int Shader::GetMatrixAttributes(const char* name) {
	unsigned int matrixLoc = glGetUniformLocation(_id, name);
	return matrixLoc;
}
unsigned int Shader::GetID() {
	return _id;
}