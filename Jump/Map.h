#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Box2D/Box2D.h"

#include "Tile.h"
namespace jump
{
	namespace map
	{
		class Map : public sf::Drawable
		{
		public:
			Map();
			~Map();

			void add_tile(map::Tile* _tile);
			void remove_tile(map::Tile* _tile);

			virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;
			void update(const sf::Event& _event, sf::RenderWindow& _window);

			void set_word(b2World* _world);

			b2World* get_world() const
			{
				return world_;
			}

		private:
			std::vector<map::Tile*> tiles_;
			b2World* world_;
		};
	}
}
