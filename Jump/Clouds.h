#pragma once

#include <random>
#include <vector>
#include <string>

#include <SFML\Graphics.hpp>

#include "Configuration.h"

namespace jump
{
	namespace objects
	{
		namespace other
		{
			class Clouds
			{
			public:
				Clouds(system::Configuration* config, sf::Vector2f spawnTime = sf::Vector2f(0, 3), sf::Vector2f speed = sf::Vector2f(20, 80), bool to_left = true, bool to_right = false);
				~Clouds();

				void draw(sf::RenderWindow& window);
				void update(float time, sf::RenderWindow& window);

				void loadTextureFromFile(std::string fileName, std::string xmlFile);
			private:
				enum Direction { LEFT, RIGHT };

				class Cloud
				{
				public:
					Cloud(float speed, Direction direction = LEFT);

					Direction getDirection();
					void setDirection(Direction direction);

					sf::Sprite& getSpirte();

					void move(float time);
					void draw(sf::RenderWindow& window);
					void setSize(float x, float y);
					void setSize(sf::Vector2f size);
				private:
					sf::Sprite _sprite;

					float _speed;
					Direction _direction;
				};

				Direction _direction;

				std::string _xmlFile;

				system::Configuration* _config;
				sf::Texture* _texture;
				sf::Vector2f _time, _speed;

				int _maxClouds, _cloudsTextures;
				float _createTime;
				sf::Clock* _clock;

				std::vector<Cloud*> _clouds;

				void create(sf::FloatRect screen);

				float rand(float min, float max);
			};
		}
	}
}