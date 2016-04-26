#include "Items.h"
#include <boost\algorithm\string.hpp>
#include <codecvt>
#include <iostream>

#include "xmlFile.h"
#include "Map.h"
#include "animationHandler.h"
#include "Animation.h"

namespace jump
{
	namespace system
	{
		namespace animations
		{
			class ItemAnimation : public Animation
			{
			public:
				ItemAnimation(sf::RectangleShape* shape, float speed = speed::MEDIUM)
				{
					initialize(speed);

					_shape = new sf::RectangleShape(*shape);
					_texture = new sf::Texture(*shape->getTexture());
					_shape->setTexture(_texture);
					_shape->setTextureRect(shape->getTextureRect());
					_shape->setPosition(shape->getPosition());

					_alpha = 255;
					std::cout << _alpha << std::endl;
					_position = shape->getPosition();
				}

				virtual void update()
				{
					_alpha-= 1;

					if (_alpha >= 0 && _alpha <= 255)
					{
						_shape->setFillColor(sf::Color(255, 255, 255, _alpha));
					}
					else if (_alpha < 0)
					{
						_shape->setFillColor(sf::Color(255, 255, 255, 0));
					}

					std::cout << _alpha << std::endl;

					if (_alpha <= 0) this->stop();
				}

				virtual void draw(sf::RenderWindow& window)
				{
					std::cout << "drawing" << std::endl;
					window.draw(*_shape);
				}

				virtual ~ItemAnimation()
				{
					delete _shape;
					delete _texture;
				}

			private:
				int _alpha;
				Position _position;
				sf::RectangleShape* _shape;
				sf::Texture* _texture;
			};
		}
	}
}

using namespace jump;
using namespace objects;
using namespace other;
using namespace system::xml;

Items::Items(int number, Items::Type type)
{
	this->number = number;
	this->privNumber = items().size();
	this->items().push_back(this);
	this->type = type;

	textureName[NONE] = "";
	textureName[BRONZE_COIN] = "coinBronze";
	textureName[GOLD_COIN] = "coinGold";
	textureName[SILVER_COIN] = "coinSilver";
	textureName[STAR] = "star";
	textureName[SPIKES] = "spikes";
	textureName[PLANT] = "plant";
	textureName[BUSH] = "bush";
	textureName[TREE] = "cactus";
	textureName[HEART] = "mushroomBrown";

	switch (type)
	{
	case Type::BRONZE_COIN:
		value = 10;
		break;
	case Type::GOLD_COIN:
		value = 1000;
		break;
	case Type::SILVER_COIN:
		value = 100;
		break;
	case Type::STAR:
		value = -1;
		break;
	case Type::SPIKES:
		value = -1;
		break;
	case Type::BUSH:
		value = -1;
		break;
	case Type::HEART:
		value = -1;
		break;
	case Type::TREE:
		value = -1;
		break;
	case Type::PLANT:
		value = -1;
		break;
	case Type::NONE:
		value = -1;
		break;
	}

	body = NULL;
}


Items::~Items()
{
	//system::AnimationHandler::getInstance().addAnimation(new system::animations::ItemAnimation(&rect));

	auto vector = items();

	this->items().erase(this->items().begin() + this->privNumber);
	for (int i = this->privNumber; i < this->items().size(); i++)
	{
		this->items()[i]->number--;
		this->items()[i]->privNumber--;
	}
}

Items::Type Items::getTypeFromWString(std::wstring type)
{
	boost::to_upper(type);

	if (type == L"BRONZE_COIN") return Type::BRONZE_COIN;
	if (type == L"SILVER_COIN") return Type::SILVER_COIN;
	if (type == L"GOLD_COIN") return Type::GOLD_COIN;
	if (type == L"TREE") return Type::TREE;
	if (type == L"HEART") return Type::HEART;
	if (type == L"STAR") return Type::STAR;
	if (type == L"SPIKES") return Type::SPIKES;
	if (type == L"BUSH") return Type::BUSH;
	if (type == L"PLANT") return Type::PLANT;

	return Type::NONE;
}

Items::Type Items::getTypeFromString(std::string type)
{
	std::wstring tmp;
	tmp.append(type.begin(), type.end());

	return Items::getTypeFromWString(tmp);
}

std::wstring Items::typeToWString(Items::Type type)
{
	switch (type)
	{
	case Type::BRONZE_COIN:
		return L"bronze_coin";
	case Type::GOLD_COIN:
		return L"gold_coin";
	case Type::SILVER_COIN:
		return L"silver_coin";
	case Type::HEART:
		return L"heart";
	case Type::TREE:
		return L"tree";
	case Type::STAR:
		return L"star";
	case Type::SPIKES:
		return L"spikes";
	case Type::BUSH:
		return L"bush";
	case Type::PLANT:
		return L"plant";
	case Type::NONE:
		return L"none";
	}
}

void Items::setPosition(float x, float y)
{
	this->setPosition(sf::Vector2f(x, y));
}

void Items::setPosition(sf::Vector2f position)
{
	position.x *= size.x;
	position.y *= size.y;

	this->rect.setPosition(position);

	if (body) body->SetTransform(b2Vec2(position.x / map::PIXELS_IN_METERS, position.y / map::PIXELS_IN_METERS), body->GetAngle());
}

void Items::setSize(sf::Vector2f size)
{
	this->size = size;

	this->rect.setSize(size);
}

sf::Vector2f Items::getSize()
{
	return size;
}

void Items::setValue(int value)
{
	if (value >= 0) this->value = value;
}

int Items::getValue()
{
	return this->value;
}

void Items::setType(Type type)
{
	this->type = type;
}

Items::Type Items::getType()
{
	return type;
}

sf::RectangleShape& Items::getRectangle()
{
	return rect;
}

sf::Texture& Items::getTexture()
{
	return texture;
}

b2Body* Items::getBody()
{
	return body;
}

void Items::createBody(b2World* world)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(rect.getPosition().x / map::PIXELS_IN_METERS, rect.getPosition().y / map::PIXELS_IN_METERS);
	bodyDef.fixedRotation = true;

	body = world->CreateBody(&bodyDef);
	body->SetUserData(this);

	b2PolygonShape bodyShape;
	b2FixtureDef bodyFixDef;
	bodyFixDef.isSensor = true;
	bodyShape.SetAsBox((rect.getSize().x / map::PIXELS_IN_METERS) / 2, (rect.getSize().y / map::PIXELS_IN_METERS) / 2);
	bodyFixDef.shape = &bodyShape;
	bodyFixDef.density = 0;
	bodyFixDef.friction = 0;

	b2Fixture* fix = body->CreateFixture(&bodyFixDef);
	fix->SetUserData((void*)map::Type::ITEM);
}

void Items::setNumber(int number)
{
	this->number = 0;
}

int Items::getNumber()
{
	return this->number;
}

std::string Items::typeToString(Items::Type type)
{
	std::wstring tmp = Items::typeToWString(type);
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	return converter.to_bytes(tmp);
}

void Items::loadTextureFromFile(std::string pathToTextures, std::string fileName, std::string xmlPath)
{
	sf::IntRect rect = getRectFromXMLFile(xmlPath + fileName, "name", textureName[type]);

	this->texture.loadFromFile(pathToTextures+fileName, rect);
	this->rect.setTexture(&texture);
}

void Items::draw(sf::RenderWindow& window, bool debug)
{
	window.draw(rect);
}

std::vector<Items*>& Items::items()
{
	static std::vector<Items*> v;
	return v;
}

void Items::move(float time, sf::Vector2f velocity)
{
	return;
}