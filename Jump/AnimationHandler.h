#pragma once

#include <vector>
#include "Animation.h"
#include <memory>

namespace jump
{
	namespace system
	{
		class AnimationHandler
		{
			AnimationHandler();
			AnimationHandler(AnimationHandler&);

			std::vector<std::shared_ptr<Animation>> _items;
		public:
			static AnimationHandler& getInstance();

			AnimationHandler& addAnimation(Animation* animation, float sleep);
			AnimationHandler& addAnimation(Animation* animation, bool pause = false);
			AnimationHandler& addAnimation(Animation* animation, Animation* runAfterThisAnimation);

			AnimationHandler& addAnimation(std::shared_ptr<Animation> animation, float sleep);
			AnimationHandler& addAnimation(std::shared_ptr<Animation> animation, bool pause = false);
			AnimationHandler& addAnimation(std::shared_ptr<Animation> animation, std::shared_ptr<Animation> afterAnimation);

			AnimationHandler& deleteAnimation(int index);
			void update();
			void draw(sf::RenderWindow& window);
			AnimationHandler& deleteAll();

			std::vector<std::shared_ptr<Animation>> getAnimations();

			~AnimationHandler();
		};
	}
}