#pragma once

#include "Menu.h"

#include "FadeIn.h"
#include "FadeOut.h"

namespace jump
{
	namespace menu
	{
		class SplashScreen : public Menu
		{
		public:
			SplashScreen(sf::RenderWindow& window, Menu* _parent = nullptr);
			~SplashScreen();

			void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
			void update(sf::RenderWindow& window) override;

		private:
			sf::Texture* texture_;
			sf::Sprite* sprite_;

			system::animations::FadeIn* fade_in_;
			system::animations::FadeOut* fade_out_;
		};
	}
}

