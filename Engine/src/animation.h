#ifndef ANIMATION_H
#define ANIMATION_H
#include "export.h"
#include "glm.hpp"
#include <vector>
namespace Engine {

	class Time;
	enum class ENGINE_API AnimationState {
		idle, moving, jumping, attacking, interacting, damage,dead // enumerador que indica estado de animación, pensar forma de utilizar
	};

	struct ENGINE_API AnimationData { // estructura con información sobre la animacion
		int _beginIndex = 0;
		int _endIndex = 0;
		float animationSpeed;
		bool hasEnded = false;
		bool loop = true;
	};

	class Sprite;
	class ENGINE_API Animation {
		Sprite* sprite;
		AnimationState state;
		glm::ivec2 dimensions;
		int _firstIndex = 0;
		int _lastIndex = 0;
		int _currentIndex = 0;
		int _actualCurrentIndex = 0;

		int _currentAnimation = 0;

		float _currentTime = 0;
		float _time = 0;
		float _lenght = 0;

		float animationSpeed = 0;


		std::vector<AnimationData> animation;
	public:
		Animation();
		~Animation();
		void Init(Sprite* texture, const glm::ivec2& tileDims);
		glm::vec4 GetUVs(int index);
		void UpdateIndex(Time& time);
		void SetAnimationSpeed(float speed);
		int GetCurrentIndex();
		void AddAnimation(int beginIndex, int endIndex, bool isLoopable, float animationSpeed);
		AnimationData GetCurrentAnimation();
		void SetAnimation(int index);
	};

}
#endif // !ANIMATION_H

