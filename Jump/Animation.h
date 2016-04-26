#pragma once

#include <SFML\Graphics.hpp>
#include <memory>

namespace jump
{
	namespace system
	{
		class AnimationHandler;

		class Animation
		{
		public:
			virtual void update() = 0;
			virtual void draw(sf::RenderWindow& window) = 0;
			
			void updatePauseTimer();

			void stop();
			bool isRunning();
			bool isPaused();
			void sleep(float time);
			void runAfterEnd(std::shared_ptr<Animation> animation);
			void pause();

			virtual ~Animation();

		protected:
			void initialize(float speed);
			Animation(float speed);
			Animation();

		private:
			std::shared_ptr<Animation> _animation;
			float _pauseTime, _speed;
			bool _isRun, _isPaused;

			sf::Clock* _pauseClock,* _clock;

			friend AnimationHandler;
		};

		namespace animations
		{
			namespace speed
			{
				const float MEDIUM = 0.08f;
				const float VERYSLOW = 1.f;
				const float SLOW = 0.5f;
				const float FAST = 0.05f;
				const float VERYFAST = 0.f;
			}
		}
	}
}
