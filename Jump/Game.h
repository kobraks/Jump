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
		Menu* menu_;

		void show_frame_rate(bool show, sf::Time time);
		void parse_events();
		void update();
		void draw();
	};

}
