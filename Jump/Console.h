#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <map>

namespace jump
{
	namespace system
	{
		class Console
		{
		public:
			static Console& getInstance();

			void update();
			void draw(sf::RenderWindow& window);
			void display(bool display);
			bool display();
			void setFont(sf::Font* font);

			~Console();

			std::string getCommand();
			std::string getArgument(int num = 0);

		private:
			Console();
			Console(Console&);

			std::wstring command;

			sf::RectangleShape console, commandBar;
			sf::Text text;
			bool _display;

			class Token
			{
			public:
				std::string value;
				char op;

				Token(std::string value, char op = 'V');
			};

			class Tokenizer {
			public:
				Tokenizer(std::string input);
				void tokenize(std::vector<Token*>& tokens);
			private:
				std::string input, temp;
			} *tokenizer;

			class Parser
			{
			public:
				Parser(std::vector<Token*> tokens);

				std::map<std::string, std::vector<std::string>> lunch();
			private:
				std::vector<Token*> tokens;
				int i;
			};

			std::vector <Token*> tokens;
		};


	}
}