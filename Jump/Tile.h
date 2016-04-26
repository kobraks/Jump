#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

namespace jump
{
	namespace map
	{
		class Tile
		{
		public:
			virtual void draw(sf::RenderWindow& window, bool debug = false) = 0;
			virtual void update() = 0;
			virtual void move(float time, sf::Vector2f velocity) = 0;
			virtual sf::FloatRect getGlobalBounds() = 0;
			virtual b2Body* getBody() = 0;

			virtual ~Tile() {};
		};
	}
}