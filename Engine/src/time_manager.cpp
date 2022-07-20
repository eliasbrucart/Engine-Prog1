#include "time_manager.h"

using namespace Engine;

Time::Time() {
	_time = 0.0f;
	_deltaTime = std::chrono::duration<float>(0.0f);
	_fps = 0.0f;
	_fpsElapesedTime = 0.0f;
	_frames = 0;
}

Time::~Time() {

}

void Time::Tick() {
	_currentTime = std::chrono::system_clock::now();
	_deltaTime = _currentTime - _prevTime;
	Reset();
	_time += _deltaTime.count();
}

void Time::Reset() {
	_prevTime = std::chrono::system_clock::now();
}

void Time::CalculateFPS() {
	_fps = 1.0f / _deltaTime.count();
}

float Time::GetFPS() {
	return _fps;
}

float Time::GetDeltaTime() {
	return _deltaTime.count();
}

float Time::GetTime() {
	return _time;
}
