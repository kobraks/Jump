#include "Tail.h"

#include <iostream>

#include "Log.h"
#include "Map.h"

#define CATEGORY(num) (1 << (num))

#pragma region usesfullFunctions

namespace jump
{
	namespace map
	{
		sf::Vector2f& operator*= (sf::Vector2f& vector, const sf::Vector2f& vector2)
		{
			vector.x *= vector2.x;
			vector.y *= vector2.y;

			return vector;
		}
	}
}

#pragma endregion

using namespace jump;
using namespace map;

Tail::Tail()
{
	number = 0;
	//sprite.setSize(sf::Vector2f(32, 32));
	//sprite.set
	sprite.scale(32, 32);
	can_display = false;
	is_Wall = false;
	is_moving = false;
	moveMin = sf::Vector2f(0, 0);
	moveMax = sf::Vector2f(0, 0);

	size = sf::Vector2f(32, 32);

	//this->sprite.setOrigin(size.x / 2, size.x / 2);
	//this->sprite.setOrigin(size.x / 2, size.x / 2);

	speed = 120;

	left = false;
	up = false;

	body = NULL;
}

Tail::~Tail()
{
}

void Tail::createBody(b2World* world)
{
	if (!this->isWall()) return;
	FILE_LOG(logINFO) << "Create Tail body";
	b2BodyDef bodyDef;

	float32 x = sprite.getPosition().x / PIXELS_IN_METERS;
	float32 y = (sprite.getPosition().y - 15) / PIXELS_IN_METERS;

	FILE_LOG(logDEBUG4) << "Tail position x: " << x << " y: " << y;

	bodyDef.position.Set(x, y);

	this->body = world->CreateBody(&bodyDef);

	b2PolygonShape bodyShape;
	bodyShape.SetAsBox((this->size.x / 2) / PIXELS_IN_METERS, (this->size.y / 2) / PIXELS_IN_METERS);
	body->SetUserData((void*)1);

	body->CreateFixture(&bodyShape, 1.0f);
}

void Tail::draw(sf::RenderWindow& window, bool debug)
{
	if (can_display) window.draw(sprite);
}

void Tail::setPosition(sf::Vector2f position)
{
	position *= size;

	this->sprite.setPosition(position);

	this->position = position;

	if (body) body->SetTransform(this->position.getBox2dPosition(), body->GetAngle());
}

sf::Vector2f Tail::getSize()
{
	return this->size;
}

void Tail::setSize(sf::Vector2f size)
{
	this->size = size;

	sprite.setScale(size.x / sprite.getTextureRect().width, size.y / sprite.getTextureRect().height);
	if (body)
	{
		body->DestroyFixture(body->GetFixtureList());

		b2PolygonShape bodyShape;
		bodyShape.SetAsBox((this->size.x / 2) / PIXELS_IN_METERS, (this->size.y / 2) / PIXELS_IN_METERS);
		body->SetUserData((void*)1);

		body->CreateFixture(&bodyShape, 1.0f);
	}
}

unsigned int Tail::getNumber()
{
	return this->number;
}

void Tail::setNumber(Tail::uint number)
{
	this->number = number;
}

bool Tail::display()
{
	return this->can_display;
}

void Tail::display(bool display)
{
	this->can_display = display;
}

void Tail::isWall(bool wall)
{
	this->is_Wall = wall;
}

bool Tail::isWall()
{
	return this->is_Wall;
}

sf::Sprite& Tail::getSprite()
{
	return this->sprite;
}

bool Tail::moving()
{
	return this->is_moving;
}

void Tail::moving(bool moving)
{
	this->is_moving = moving;
}

void Tail::setMoveMin(sf::Vector2f moveMin)
{
	moveMin.x *= (-1);
	moveMin.y *= (-1);

	this->moveMin = moveMin;
}

void Tail::setMoveMax(sf::Vector2f moveMax)
{
	this->moveMax = moveMax;
}

sf::Vector2f Tail::getMoveMin()
{
	return this->moveMin;
}

sf::Vector2f Tail::getMoveMax()
{
	return this->moveMax;
}

void Tail::setSpeed(int speed)
{
	this->speed = speed;
}

int Tail::getSpeed()
{
	return this->speed;
}

void Tail::move(float time, sf::Vector2f velocity)
{
	if (is_moving)
	{
		sf::Vector2i max, min;

		if (this->moveMin.x == 0 && this->moveMax.x == 0)
		{
			velocity.x = 0;
		}
		else 	if (this->moveMin.x != 0 || this->moveMax.x != 0)
		{
			velocity.x *= time;
			velocity.x *= speed;

			min.x = position.getSFPosition().x / size.x - moveMin.x;
			max.x = position.getSFPosition().x / size.x + moveMax.x;

			int x = sprite.getPosition().x / size.x;
			
			if (max.x == x) left = true;
			else 	if (min.x == x) left = false;

			if (left) velocity.x *= (-1);
		}

		if (this->moveMin.y == 0 && this->moveMax.y == 0)
		{
			velocity.y = 0;
		}
		else 	if (moveMin.y != 0 || this->moveMax.y != 0)
		{
			velocity.y *= time;
			velocity.y *= speed;

			min.y = position.getSFPosition().y / size.y - moveMin.y;
			max.y = position.getSFPosition().y / size.y + moveMax.y;

			int y = sprite.getPosition().y / size.y;

			if (max.y == y) up = true;
			else 	if (min.y == y) up = false;

			if (up) velocity.y *= (-1);
		}

		float32 x = sprite.getPosition().x / PIXELS_IN_METERS;
		float32 y = (sprite.getPosition().y - 15) / PIXELS_IN_METERS;

		this->sprite.move(velocity);
		this->body->SetTransform(b2Vec2(x, y), this->body->GetAngle());
	}
}

b2Body* Tail::getBody()
{
	return this->body;
}