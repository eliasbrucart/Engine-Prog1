#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include"sprite.h"
#include "animation.h"
#include "time_manager.h"

namespace Engine {
	Sprite::Sprite(bool transparency, Renderer* renderer, Shader shader) : Entity2D() {
		_transparency = transparency;
		_renderer = renderer;
		this->shader = shader;
		_texImporter = new TextureImporter();

		uv[0].u = 1; uv[0].v = 1;
		uv[1].u = 1; uv[1].v = 0;
		uv[2].u = 0; uv[2].v = 0;
		uv[3].u = 0; uv[3].v = 1;
	}

	Sprite::Sprite(bool transparency, const char* path, Renderer* renderer, Shader shader) : Entity2D() {
		_transparency = transparency;
		_renderer = renderer;
		_texImporter = new TextureImporter();
		this->shader = shader;
		_texImporter->SetPath(path);

		uv[0].u = 1; uv[0].v = 1;
		uv[1].u = 1; uv[1].v = 0;
		uv[2].u = 0; uv[2].v = 0;
		uv[3].u = 0; uv[3].v = 1;
	}

	Sprite::~Sprite() {
		if (_texImporter != NULL) {
			delete _texImporter;
			_texImporter = NULL;
		}
	}

	void Sprite::GenerateVAO() {
		_renderer->GenerateVAO(_vao);
	}

	void Sprite::BindVAO() {
		_renderer->BindVAO(_vao);
	}

	void Sprite::BindVBO(float* vertices, int AmmountOfVertices) {
		_renderer->BindVBO(_vbo, vertices, AmmountOfVertices);
	}

	void Sprite::BindEBO(unsigned int* indices, int AmmountOfVertices) {
		_renderer->BindEBO(_ebo, indices, AmmountOfVertices);
	}

	void Sprite::Init() {
		LoadSprite();
		_renderer->SetTexAttribPointer(shader.GetID());
		BindBuffers();
	}

	void Sprite::LoadSprite() {
		if (_texImporter)
			_texImporter->LoadImage(_width, _height, _transparency);
		else
			std::cout << "Couldn't find image" << std::endl;
	}

	void Sprite::LoadSprite(int width, int height) {
		if (_texImporter)
			_texImporter->LoadImage(width, height, _transparency);
		else
			std::cout << "Couldn't find image" << std::endl;
	}

	void Sprite::LoadSprite(int width, int height, const char* path) {
		if (_texImporter) {
			_texImporter->SetPath(path);
			_texImporter->LoadImage(width, height, _transparency);
		}
		else
			std::cout << "Couldn't find image" << std::endl;
	}

	void Sprite::BindBuffers() {
		GenerateVAO();
		BindVAO();
		BindVBO(_vertices, 32);
		BindEBO(_quadIndices, 6);
	}

	void Sprite::BindTexture() {
		glBindTexture(GL_TEXTURE_2D, _texImporter->GetTexture());
		glActiveTexture(GL_TEXTURE0);
	}

	void Sprite::BlendSprite() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Sprite::UnBlendSprite() {
		glDisable(GL_BLEND);
	}

	void Sprite::Color(float r, float g, float b){
		_vertices[3] = r;  _vertices[4] = g;  _vertices[5] = b;
		_vertices[11] = r; _vertices[12] = g; _vertices[13] = b;
		_vertices[19] = r; _vertices[20] = g; _vertices[21] = b;
		_vertices[27] = r; _vertices[28] = g; _vertices[29] = b;
	}

	void Sprite::Color(glm::vec3 color){
		   _vertices[3] = color.x;  _vertices[4] = color.y;  _vertices[5] = color.z;
		  _vertices[11] = color.x; _vertices[12] = color.y; _vertices[13] = color.z;
		  _vertices[19] = color.x; _vertices[20] = color.y; _vertices[21] = color.z;
		  _vertices[27] = color.x; _vertices[28] = color.y; _vertices[29] = color.z;
	}

	void Sprite::SetUVs(glm::vec4 uvRect) {
		//				x + ancho                   y + alto
		uv[0].u = uvRect.x + uvRect.z; uv[0].v = uvRect.y + uvRect.w;    // top right
		//				 x + ancho                   y
		uv[1].u = uvRect.x + uvRect.z; uv[1].v = uvRect.y;				 // bottom right
		//				x                  y
		uv[2].u = uvRect.x; uv[2].v = uvRect.y;							// bottom left
		//				x					y + alto
		uv[3].u = uvRect.x; uv[3].v = uvRect.y + uvRect.w;				// top left

		UpdateUVs();
	}

	void Sprite::UpdateUVs(){
		 _vertices[6] = uv[0].u;  _vertices[7] = uv[0].v;   // top Right
		_vertices[14] = uv[1].u; _vertices[15] = uv[1].v;   // bottom Right
		_vertices[22] = uv[2].u; _vertices[23] = uv[2].v;   // bottom Left
		_vertices[30] = uv[3].u; _vertices[31] = uv[3].v;   // top Left
	}

	void Sprite::DrawSprite() {
		UpdateMatrices();
		if (_transparency) {
			BlendSprite();
			BindTexture();
			_renderer->DrawSprite(shader, _vao, _vbo, _vertices, 32, GetModel());
			UnBlendSprite();
			glDisable(GL_TEXTURE_2D);
		}
		else {
			BindTexture();
			_renderer->DrawSprite(shader, _vao, _vbo, _vertices, 32, GetModel());
			glDisable(GL_TEXTURE_2D);
		}
	}

	void Sprite::DrawAnimation(glm::vec4 uvRect){
		UpdateMatrices();
		SetUVs(uvRect);
		if (_transparency) {
			BlendSprite();
			BindTexture();
			_renderer->DrawSprite(shader, _vao, _vbo, _vertices, 32, GetModel());
			UnBlendSprite();
			glDisable(GL_TEXTURE_2D);
		}
		else {
			BindTexture();
			_renderer->DrawSprite(shader, _vao, _vbo, _vertices, 32, GetModel());
			glDisable(GL_TEXTURE_2D);
		}
	}

	void Sprite::SetWidth(int width) {
		_width = width;
	}

	int Sprite::GetWidth() {
		return _width;
	}

	void Sprite::SetHeight(int height) {
		_height = height;
	}

	int Sprite::GetHeight() {
		return _height;
	}

	void Sprite::SetPath(const char* path) {
		if (_texImporter)
			_texImporter->SetPath(path);
		else
			std::cout << "Couldn't set path" << std::endl;
	}

	const char* Sprite::GetPath() {
		if (_texImporter)
			return _texImporter->GetPath();
		else
			return nullptr;
	}

	void Sprite::UnbindBuffers() {
		_renderer->UnbindBuffers();
	}

	void Sprite::DeleteBuffer() {
		_renderer->DeleteBuffers(_vao, _vbo, _ebo);
	}
}

