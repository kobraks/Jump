#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <Box2D\Box2D.h>

#include "Map.h"
#include "Configuration.h"

namespace jump
{
	namespace map
	{
		enum Type;
	}

	namespace objects
	{
		namespace characters
		{
			enum Status { alive, death, imortal };

			class Character
			{
			public:
				Character();
				virtual ~Character();

				virtual void setPosition(sf::Vector2f position) = 0;
				virtual void update(sf::Time& timeStep, map::Map* map) = 0;
				virtual void move(sf::Vector2f& vector, sf::Time time) = 0;

				virtual void create(b2World* world) = 0;
				virtual void LoadTextureFromFile(std::string fileName) = 0;

				virtual void draw(sf::RenderWindow& window) = 0;

				virtual void contact(map::Type typePlayer, map::Type typeB, b2Body* body = NULL) = 0;
				virtual void endContact(map::Type typePlayer, map::Type typeB, b2Body* body = NULL) = 0;

				float getSpeed();
				void setSpeed(float speed);

				Status getStatus();
				void setStatus(Status status);

				sf::Texture& getTexture();
				sf::RectangleShape& getRectangle();
				sf::Sprite& getSprite();
				b2Body* getBody();

				virtual int getLives() = 0;
				virtual int getPoints() = 0;
			protected:
				system::Configuration* config;
				sf::Vector2f velocity;
				int animationStep, direction;
				float speed, frameCounter, switchFrame, frameSpeed;

				sf::RectangleShape rect;

				sf::Texture texture;
				sf::Sprite sprite;
				Status status;

				b2Body* body;
			};
		}
	}
}
