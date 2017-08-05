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
				void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

				void update(sf::RenderWindow& _window) override;

				virtual ~FadeIn();
			protected:
				sf::Sprite* sprite_;
				sf::Texture* texture_;
			};
		}
	}
}