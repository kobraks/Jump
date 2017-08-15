#pragma once

#include <SFML\Graphics.hpp>

#include "Menu.h"

namespace jump
{
	namespace system
	{
		class Configuration;
	}

	class Game
	{
	public:
		Game();
		Game(int argc, char* argv[]);
		virtual ~Game();

		void run_game();
		void parse_arguments(int argc, char* argv[]);

	private:
		system::Configuration* config_;
		sf::RenderWindow* window_;
		sf::Time time_from_last_update_;
		bool show_log_, show_console_;
		Menu* menu_;

		void parse_events();
		void update();
		void draw();
	};

}
