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

			void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
			void update(sf::RenderWindow& window) override;

		private:
			Menu* menu_;
			sf::Texture* texture_button_;
			bool show_log_;
		};
	}

}
