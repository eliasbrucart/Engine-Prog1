#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "base.h"
using namespace Engine;

Base::Base(){
	_renderer = new Renderer();
	_window = new Window(1280, 720);
	_camera = new Camera(_renderer, ProjectionType::orthographic);
	collisionmanager = new CollisionManager();
}

Base::~Base() {
	if (_renderer != NULL) {
		delete _renderer;
		_renderer = NULL;
	}
	if (_window != NULL)
	{
		delete _window;
		_window = NULL;
	}
	if (_camera != NULL) {
		delete _camera;
		_camera = NULL;
	}
	if (collisionmanager != NULL) {
		delete collisionmanager;
		collisionmanager = NULL;
	}
}

void Base::Execute()
{
	Init();
	Update();
	Unload();
}

int Base::Init(){
	_window->CreateWindow("Unreal Engine pero con Intellisense");

	if (!_renderer->InitializeGlew()) {
		return 0;
	}

	basicShader.Create("..//Engine//src//Shaders//vertex.vert", "..//Engine//src//Shaders//fragment.frag");
	textureShader.Create("..//Engine//src//Shaders//texture_vert.vert", "..//Engine//src//Shaders//texture_frag.frag");
	glEnable(GL_DEPTH_TEST);
	_camera->transform.position = glm::vec3(0.0f, 0.0f, -3.0f);
	_camera->SetView(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	_camera->SetProjection(ProjectionType::orthographic);
	_camera->Init(basicShader);
	_camera->Init(textureShader);


	input.SetWindow(_window->GetWindow());

	time.Reset();

	InitGame();
}

void Base::Update(){
	float speed = 0.01f;
	while (!glfwWindowShouldClose(_window->GetWindow())){
		_renderer->BeginFrame(0.0f,0.0f,0.0f);
		//_camera->transform.position.x += speed;
		//std::cout << _camera->transform.position.x << std::endl;
		UpdateGame();
		_camera->Draw(basicShader);
		_camera->Draw(textureShader);
		time.CalculateFPS();
		time.Tick();
		_renderer->EndFrame(_window->GetWindow());
	}
}

void Base::Unload(){
	UnloadGame();
	glfwTerminate();
}

Renderer* Base::GetRenderer(){
	return _renderer;
}

Window* Base::GetWindow(){
	return _window;
}
