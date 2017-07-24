#pragma once

#include <SFML\Graphics.hpp>

namespace jump
{
	namespace system
	{
		class AnimationHandler;

		class Animation : public sf::Drawable
		{
		public:
			explicit Animation(Animation* _animation = nullptr);
			explicit Animation(float _speed, Animation* _animation = nullptr);

			virtual void update(sf::RenderWindow& _window) = 0;;
			virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const = 0;

			bool is_running() const;
			bool is_paused() const;
			void sleep(float _time);
			void run_after_end(Animation* _animation);
			void pause();
			void stop();
			void start();

			virtual ~Animation();

		protected:
			void update_pause_timer();
			void update_handler(sf::RenderWindow& _window);

		private:
			Animation* animation_;
			float pause_time_, speed_;
			bool run_, paused_;

			sf::Clock* pause_clock_,* clock_;

			friend AnimationHandler;
		};

		namespace animations
		{
			namespace speed
			{
				static const float MEDIUM = 0.08f;
				static const float VERYSLOW = 1.f;
				static const float SLOW = 0.5f;
				static const float FAST = 0.05f;
				static const float VERYFAST = 0.f;
			}
		}
	}
}
