#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "Configuration.h"
#include "Engine.h"

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

		enum GameState { NONE, GAME, OPTIONS, EXIT, GAME_OVER, MENU, SPLASCHSCREEN };

	protected:
		GameState state_;

	private:
		sf::RenderWindow* window_;
		system::Configuration*  config_;
		Engine *engine_;

		int amoutOptions;
		std::wstring* optionsNames;
		sf::Text mousePosition;

		void update();
		void draw();

		Menu* menu_;
	};

}
