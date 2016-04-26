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
				FadeIn(sf::Sprite& sprite, float speed = system::animations::speed::MEDIUM);

				virtual void update();
				virtual void draw(sf::RenderWindow& window);

				virtual ~FadeIn();
			protected:
				sf::Sprite* _sprite;
				sf::Texture* _texture;
				float _alpha;
			};
		}
	}
}