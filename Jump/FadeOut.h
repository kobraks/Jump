#pragma once

#include "Animation.h"
#include "FadeIn.h"

namespace jump
{
	namespace system
	{
		namespace animations
		{
			class FadeOut : public FadeIn
			{
			public:
				FadeOut(sf::Sprite& _sprite, float _speed = system::animations::speed::MEDIUM);

				virtual void update(sf::RenderWindow& _window);
				virtual void stage(sf::Uint16 _stage);
			};
		}
	}
}