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
			SplashScreen(Menu* _parent = nullptr);
			~SplashScreen();

			virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;

		protected:
			virtual void update(sf::Event& _event, sf::RenderWindow& _window);

		private:
			bool scaled_;

			sf::Texture* texture_;
			sf::Sprite* sprite_;

			system::animations::FadeIn* fade_in_;
			system::animations::FadeOut* fade_out_;
		};
	}
}

