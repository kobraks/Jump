#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <Box2D\Box2D.h>

#include <vector>
#include <string>

#include "Position.h"
#include "Tile.h"

namespace jump
{
	namespace map
	{
		class Map;
		class Tile;

		class Tail : public Tile
		{
		protected:
			typedef unsigned int uint;
		public:
			Tail();
			virtual ~Tail();

			unsigned int getNumber();
			void setNumber(uint number);

			sf::Vector2f getSize();
			void setSize(sf::Vector2f size);

			void setPosition(sf::Vector2f position);
			void display(bool display);
			bool display();

			bool isWall();
			void isWall(bool isWall);

			bool moving();
			void moving(bool moving);

			void setSpeed(int speed);
			int getSpeed();

			void setMoveMin(sf::Vector2f moveMin);
			sf::Vector2f getMoveMin();

			void setMoveMax(sf::Vector2f moveMax);
			sf::Vector2f getMoveMax();

			virtual void move(float timeStep, sf::Vector2f velocity = sf::Vector2f(1, 1));
			virtual void update() {};
			virtual void draw(sf::RenderWindow& window, bool debug = false);
			virtual sf::FloatRect getGlobalBounds() { return this->sprite.getGlobalBounds(); }
			virtual b2Body* getBody();

			sf::Sprite& getSprite();

			void createBody(b2World* world);

			friend Map;
		private:
			uint number;
			int speed;
			sf::Sprite sprite;

			sf::Vector2f size, moveMin, moveMax;

			bool is_Wall;
			bool can_display;
			bool is_moving;

			bool left;
			bool up;

			b2Body* body;

			system::Position position;
		};
	}
}
