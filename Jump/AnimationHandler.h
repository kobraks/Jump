#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Animation.h"

namespace jump
{
	namespace system
	{
		class AnimationHandler
		{
			AnimationHandler();

			std::vector<Animation*> animations_;;
			static AnimationHandler* get_instance();
		public:
			AnimationHandler(AnimationHandler&) = delete;

			static AnimationHandler* add(Animation* _animation);
			
			static AnimationHandler* remove_animation(const size_t& _index);
			static AnimationHandler* remove_animation(Animation* _animation);
			static AnimationHandler* update(sf::RenderWindow& _window);
			static AnimationHandler* draw(sf::RenderWindow& window);
			static AnimationHandler* clear();
			static bool contains(Animation* _animation);

			static std::vector<Animation*> get_animations();

			~AnimationHandler();
		};
	}
}
