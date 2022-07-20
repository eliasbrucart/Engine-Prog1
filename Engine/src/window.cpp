#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "window.h"
#include<iostream>

using namespace Engine;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

Window::Window() {
	_window = NULL;
	_width = 800;
	_height = 600;
}

Window::Window(int width, int height) {
	_window = NULL;
	_width = width;
	_height = height;
}

Window::~Window() {

}

int Window::CreateWindow(const char* name) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}
	// glfw window creation
	// --------------------
	_window = glfwCreateWindow(_width, _height, name, NULL, NULL);
	if (_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
}

GLFWwindow* Window::GetWindow() {
	return _window;
}

void Window::SetWidth(int width) {
	_width = width;
}

int Window::GetWidth() {
	return _width;
}

void Window::SetHeight(int height) {
	_height = height;
}

int Window::GetHeight() {
	return _height;
}