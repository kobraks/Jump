#pragma once

#include <string>
#include <vector>
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

#include "Tile.h"

namespace jump
{
	namespace map
	{
		class Tile;
	}
	namespace objects
	{
		namespace other
		{
			class Items : public map::Tile
			{
			public:
				enum Type { NONE, BRONZE_COIN, SILVER_COIN, GOLD_COIN, TREE, HEART, STAR, SPIKES, BUSH, PLANT };
				Items(int number, Items::Type type = Items::Type::NONE);
				virtual ~Items();

				static Type getTypeFromWString(std::wstring type);
				static Type getTypeFromString(std::string type);
				static std::string typeToString(Items::Type type);
				static std::wstring typeToWString(Items::Type type);

				void loadTextureFromFile(std::string pathToTextures, std::string fileName, std::string xmlPath);

				void createBody(b2World* world);

				void setPosition(float x, float y);
				void setPosition(sf::Vector2f position);

				void setValue(int value);
				int getValue();

				void setNumber(int number);
				int getNumber();

				void setType(Type type);
				Type getType();

				sf::Vector2f getSize();
				void setSize(sf::Vector2f size);

				virtual void draw(sf::RenderWindow& window, bool debug = false);
				virtual void move(float time = 0, sf::Vector2f velocity = sf::Vector2f(0, 0));
				virtual void update(){}
				virtual sf::FloatRect getGlobalBounds() { return this->rect.getGlobalBounds(); }
				virtual b2Body* getBody();

				sf::RectangleShape& getRectangle();
				sf::Texture& getTexture();
			private:
				Type type;

				sf::RectangleShape rect;
				sf::Texture texture;
				b2Body* body;
				sf::Vector2f size;

				std::map<Items::Type, std::string> textureName;

				int value, number, privNumber;
				static std::vector<Items*>& items();
			};
		}
	}
}
