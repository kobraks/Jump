#pragma once

#include <string>
#include <vector>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

#include "Tail.h"
#include "Configuration.h"
#include "Character.h"
#include "MapFiles.h"
#include "Items.h"
#include "Clouds.h"

namespace jump
{
	namespace objects
	{
		namespace characters
		{
			class Character;
		}
	}

	namespace map
	{
		const float PIXELS_IN_METERS = 50.0f;

		enum Type
		{
			BOX = 1,
			PLAYER,
			PLAYER_FOOT_SENSOR,
			PLAYER_HEAD_SENSOR,
			ENEMY,
			ITEM
		};

		class Map
		{
		protected:
			typedef unsigned int uint;
		public:
			Map(system::Configuration* config);

			bool LoadFromFile(std::string fileName, sf::RenderWindow* window);
			void SaveToFile(std::string fileName);

			void updatePlatforms(sf::Time time, sf::FloatRect screen);

			void draw(sf::RenderWindow& window);

			sf::Vector2f getStartPosition();
			sf::Vector2f getEndPosition();
			std::wstring getNextMap();
			std::vector<Tile*>& getItems();

			void setNextmap(std::wstring);

			uint getGroundPosition();
			float getGravityForce();

			virtual ~Map();

			void clear();
			void update(sf::Time time, objects::characters::Character* player, sf::RenderWindow& window);

			b2World* getWorld();
			sf::Texture& getTexture();

			std::string fileName;
		private:
			std::wstring name, nextMap;

			system::Configuration* config;

			uint height, width;
			uint groundHeight;
			float gravity;

			std::vector<Tile*> items;

			sf::Vector2f tailSize;
			sf::Vector2f startPosition;
			sf::Vector2f viewStartPosition;

			sf::Vector2f endPosition;

			sf::Texture texture, bacgroundTexture;
			sf::RectangleShape rect;
			b2World* world;

			void createTials(int i, mapf::MapFiles& map);
			void createItem(int i, mapf::MapFiles& map);
			void createEnemy(int i, mapf::MapFiles& map);

			objects::other::Clouds* cloud;
		};
	}
}