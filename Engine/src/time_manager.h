#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H
#include "export.h"
#include <chrono>
namespace Engine {
	class ENGINE_API Time {
	private:
		std::chrono::system_clock::time_point _prevTime;
		std::chrono::system_clock::time_point _currentTime;
		std::chrono::duration<float> _deltaTime;
		float _time = 0;
		float _fps;
		float _fpsElapesedTime;
		int _frames;

	public:
		Time();
		~Time();

		void Tick();
		void Reset();
		void CalculateFPS();

		float GetFPS();
		float GetDeltaTime();
		float GetTime();
	};
}


#endif // !TIME_MANAGER_H

