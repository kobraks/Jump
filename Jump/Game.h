#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "Configuration.h"
#include "Log.h"
#include "Engine.h"

namespace jump
{
	class Game
	{
	public:
		Game();
		virtual ~Game();

		void runGame();
		void processArguments(int argc, char* argv[]);

		enum GameState { NONE, GAME, OPTIONS, EXIT, GAME_OVER, MENU, SPLASCHSCREEN };

	protected:
		GameState state;

	private:
		sf::RenderWindow* window;
		sf::Font* titleFont;
		sf::Font* optionsFont;
		sf::Font* authorFont;
		sf::Font* debugFont;
		system::Configuration*  config;
		Engine *engine;

		int amoutOptions;
		std::wstring* optionsNames;
		sf::Text mousePosition;

		void update();
		void draw();
		void createMenu();
		void splaschScreen(std::string fileName);
	};

}
