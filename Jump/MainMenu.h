#pragma once

#include <SFML/Graphics.hpp>

#include "Menu.h"

namespace jump
{
	namespace menu
	{
		class MainMenu : public Menu
		{
		public:
			MainMenu(sf::RenderWindow& _window, Menu* _parent = nullptr);
			~MainMenu();

			virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;

		protected:
			virtual void update(const sf::Event& _event, sf::RenderWindow& _window);

		private:
			Menu* menu_;
			sf::Texture* texture_button_;
		};
	}

}
