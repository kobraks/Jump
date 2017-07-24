#pragma once

#include "Animation.h"

namespace jump
{
	namespace system
	{
		namespace animations
		{
			class FadeIn : public system::Animation
			{
			public:
				FadeIn(sf::Sprite& _sprite, float _speed = system::animations::speed::MEDIUM);
				virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;

				virtual void update(sf::RenderWindow& _window);

				virtual ~FadeIn();
			protected:
				sf::Sprite* sprite_;
				sf::Texture* texture_;
				float alpha_;
			};
		}
	}
}