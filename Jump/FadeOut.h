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
				FadeOut(sf::Sprite& sprite, float speed = system::animations::speed::MEDIUM);

				virtual void update();
			};
		}
	}
}