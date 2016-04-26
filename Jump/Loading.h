#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include <thread>
#include <map>

namespace jump
{
	namespace system
	{
		class Loading
		{
		public:
			static Loading& getInstance();
			~Loading();

			void initialize(sf::Font* font, int value = 0, int maxValue = 100, int loadingStep = 10);
			void start(sf::RenderWindow* window, bool showFPS = false, bool debug = false);

			void setMaxValue(int maxValue);
			void setValue(int value);
			void setLoadingStep(int step);

			int getValue();
			int getMaxValue();
			int getLoadingStep();

			void setFont(sf::Font* font);

			void draw(sf::RenderWindow& window);

			void loadTextureFromFile(std::map<std::string, std::string> fileName);

			void add();
			void add(const int& number);

			void stop();

			Loading& operator+=(const int number);
			Loading& operator++();
		private:
			Loading();
			Loading(Loading&);

			int value, maxValue, loadingStep;
			float rotation;
			bool isWorking;
			sf::Text text;
			sf::Texture textureWheel, textureBar;
			sf::RectangleShape wheel, loadingBar;
			std::thread* thread;

			void loading(sf::RenderWindow* window, bool debug, bool showFPS);
		};
	}
}