#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Character.h"

namespace jump
{
	namespace system
	{
		class Hud
		{
		public:
			~Hud();

			static Hud& getInstance();
			Hud* getPointer();

			void draw(sf::RenderWindow& window);
			void update(sf::RenderWindow& window);

			objects::characters::Character* getPlayer();
			void setPlayer(objects::characters::Character* player);

			sf::Texture* getTexture();

			void xml(std::string xmlfile);
		private:
			Hud();
			Hud(Hud&);

			objects::characters::Character* _player;

			int _lives, _maxLives;
			std::string _points;

			sf::RectangleShape _bar, *_rect;;
			sf::Texture* _texture;

			sf::IntRect* _numbers, *_hearts;

			std::vector<sf::RectangleShape* > _PointsNumbers;
		};


	}
}
