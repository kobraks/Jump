#pragma once

#include <SFML\Graphics.hpp>
#include <map>
#include <queue>

#include "Configuration.h"
#include "Map.h"
#include "Player.h"


namespace jump
{
	class Engine : b2ContactListener
	{
	public:
		Engine(system::Configuration* config);
		~Engine();

		void runEngine(sf::RenderWindow* window);
		void update(sf::Time timeStep, sf::RenderWindow* window);
		void draw(sf::RenderWindow& window);
		void reload(sf::RenderWindow* window);
	private:
		struct Remover
		{
			void* pointer;
			map::Type type;

			Remover(void* pointer, map::Type type);
		};

		system::Configuration* config;
		map::Map* map;
		objects::characters::Player* player;
		bool game;
		float acelerator;

		sf::Text playerSpeed;

		std::vector<objects::characters::Character*> enemy;
		std::queue<Remover*> toRemove;

		void destroyBody();

	protected:
		void BeginContact(b2Contact* c);
		void EndContact(b2Contact* c);
	};
}
