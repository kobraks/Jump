#pragma once

#include <SFML\Graphics.hpp>

#include <string>
#include <map>

namespace jump
{
	namespace system
	{
		class Configuration
		{
		public:
			Configuration();
			virtual ~Configuration();

			void loadFromFile(std::wstring name);
			void save();
			std::string fontPath;
			std::map <std::string, std::string> fontNames;
			std::map <std::string, std::string> loadingTextures;
			bool debug, showFPS;

			std::string pathToInterface;
			std::string texturesPath;
			std::string playerTextures;
			std::string mapTextures;
			std::string dataFile;
			std::string xmlFiles;
			std::string itemsTextures;
			std::string hudTextures;
			std::wstring startMap;

			int width, height, maxClouds;

			sf::Font* debugFont;
			sf::Font* font;

			sf::Keyboard::Key up, left, right, down;
		private:
			std::wstring name;
		};


	}
}