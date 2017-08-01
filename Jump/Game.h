#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "Configuration.h"

#include "Menu.h"
#include "MainMenu.h"

namespace jump
{
	class Game
	{
	public:
		Game();
		Game(int argc, char* argv[]);
		virtual ~Game();

		void run_game();
		void parse_arguments(int argc, char* argv[]);

	private:
		sf::RenderWindow* window_;

		sf::Text mouse_position_;

		void update();
		void draw();

		Menu* menu_;
	};

}
