#pragma once

#include <map>
#include <SFML/Graphics/Font.hpp>
#include <string>

namespace jump
{
	namespace system
	{
		class FontCointainer
		{
		public:
			FontCointainer(FontCointainer&) = delete;

			static FontCointainer* get_instance();

			static sf::Font* get_font(std::string _name);
			static FontCointainer* add_font(std::string _name, sf::Font* _font);

			~FontCointainer();

		private:
			FontCointainer();
			sf::Font* find(std::string _name);

			std::map<std::string, sf::Font*> fonts_;
		};
	}
}