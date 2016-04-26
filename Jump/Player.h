#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <string>
#include <vector>

#include "Character.h"
#include "Bust.h"

namespace jump
{
	namespace objects
	{
		namespace characters
		{
			class Player : public Character
			{
			public:
				Player(system::Configuration* config);
				~Player();

				virtual void setPosition(sf::Vector2f position);
				virtual void update(sf::Time& timeStep, map::Map* map);
				virtual void move(sf::Vector2f& vector, sf::Time time);
				void stand();
				virtual void create(b2World* world);
				virtual void LoadTextureFromFile(std::string fileName);

				virtual void draw(sf::RenderWindow& window);

				virtual void contact(map::Type typePlayer, map::Type typeB, b2Body* body = NULL);
				virtual void endContact(map::Type typePlayer, map::Type typeB, b2Body* body = NULL);

				virtual int getLives();
				virtual int getPoints();
			private:
				float lives;

				int numFootContacts;
				int jumpTimeout;
				int score;

				void animation(sf::Vector2f& vector, sf::Time& time);
				bool canBeKilled();
				std::vector<system::Bust*> busts;
			};
		}
	}
}
