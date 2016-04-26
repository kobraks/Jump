#pragma once

#include <string>
#include <SFML\Graphics.hpp>
#include <ostream>

namespace jump
{
	namespace system
	{
		class FrameRate
		{
		public:
			static FrameRate& getInstance();

			~FrameRate();

			void update();
			void draw(sf::RenderWindow& window);
			void setPosition(sf::Vector2f position);
			sf::Vector2f getPosition();
			void setFont(sf::Font* font);
			void initiate();

			friend std::ostream& operator<< (std::ostream& out, const FrameRate& frame)
			{
				out << frame.times;

				return out;
			}

		private:
			FrameRate();
			FrameRate(sf::Font* debugFont);
			FrameRate(FrameRate&);

			sf::Clock* clock;
			sf::Time time;

			std::string times;
			sf::Text text;
		};

	}
}
