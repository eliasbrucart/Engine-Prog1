#include "animation.h"
#include "time_manager.h"
#include <iostream>

Engine::Animation::Animation() {
	sprite = NULL;
	dimensions = glm::ivec2(0, 0);
	state = AnimationState::idle;
}

Engine::Animation::~Animation() {
}

void Engine::Animation::Init(Sprite* texture, const glm::ivec2& tileDims) {
	sprite = texture;
	dimensions = tileDims;

}

glm::vec4 Engine::Animation::GetUVs(int index) {
	int xTile = index % dimensions.x; // se hace para que cuando el indice sea mayor a la dimension en x, vuelva a ser 0, es decir, se "reinicia" el ciclo en x
	int yTile = index / dimensions.x;

	//                      x  y   w   h
	glm::vec4 uv = glm::vec4(0, 0, 0, 0);

	uv.x = xTile / static_cast<float>(dimensions.x); // X
	uv.y = yTile / static_cast<float>(dimensions.y); // Y
	uv.z = 1.0f / dimensions.x; // Ancho / W
	uv.w = 1.0f / dimensions.y; // Alto / H

	return uv;
}

void Engine::Animation::UpdateIndex(Time& time) {
	float length = 1.0f * 1000;
	_currentTime += time.GetDeltaTime() * animationSpeed;

	while (_currentTime > length) {
		_currentTime -= length;
	}

	int framesAmmount = (animation[_currentAnimation]._endIndex - animation[_currentAnimation]._beginIndex);


	if (!animation[_currentAnimation].hasEnded) { // pregunto si la animacion no termino
		_actualCurrentIndex = animation[_currentAnimation]._beginIndex;

		_actualCurrentIndex = _actualCurrentIndex + static_cast<int>(_currentTime) % framesAmmount;

		if (!animation[_currentAnimation].loop && _actualCurrentIndex >= animation[_currentAnimation]._endIndex-1) { // pregunto si la animacion no es loopeable y si ya llego al ultimo indice
			_actualCurrentIndex = animation[_currentAnimation]._endIndex-1; //seteo el indice al ultimo frame de la animacion
			animation[_currentAnimation].hasEnded = true;					// indico que termino la animación
		}
	}
	else {
		_actualCurrentIndex = animation[_currentAnimation]._endIndex -1; // si termino la animacion y no es loopeable, seteo el indice al ultimo frame de la animación
	}

}

void Engine::Animation::SetAnimationSpeed(float speed) {
	if (speed < 0)
		speed *= -1;

	animation[_currentAnimation].animationSpeed = speed * 10;
}

int Engine::Animation::GetCurrentIndex() {
	return _actualCurrentIndex;
}

void Engine::Animation::AddAnimation(int beginIndex, int endIndex, bool isLoopable, float animationSpeed) {
	AnimationData newAnim;
	newAnim._beginIndex = beginIndex;
	newAnim._endIndex = endIndex;
	newAnim.loop = isLoopable;
	newAnim.animationSpeed = animationSpeed * 10;
	animation.push_back(newAnim); 
}

Engine::AnimationData Engine::Animation::GetCurrentAnimation() {
	return animation[_currentAnimation];
}

void Engine::Animation::SetAnimation(int index) {
	_currentAnimation = index;
	_firstIndex = animation[_currentAnimation]._beginIndex;
	_lastIndex = animation[_currentAnimation]._endIndex;
	if(animationSpeed != animation[_currentAnimation].animationSpeed)
	animationSpeed = animation[_currentAnimation].animationSpeed;

	if (_currentIndex < _firstIndex || _currentIndex > _lastIndex)
		_actualCurrentIndex = _firstIndex;


	// si termino la animación y el boton sigue presionado, se resetea la animacion y no se auto superpone
	if (animation[_currentAnimation].hasEnded || (_actualCurrentIndex >= _lastIndex || _actualCurrentIndex < _firstIndex)) {
		animation[_currentAnimation].hasEnded = false;
		_currentTime = 0;
	}
}

