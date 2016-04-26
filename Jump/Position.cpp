#include "Position.h"

#include "Map.h"

using namespace jump;
using namespace system;

Position::Position()
{
	this->set(sf::Vector2f(0, 0));
}

Position::Position(const sf::Vector2f& position)
{
	set(position);
}

Position::Position(const b2Vec2& position)
{
	set(position);
}

void Position::set(const sf::Vector2f& position)
{
	sfml.x = position.x;
	sfml.y = position.y;
	box2d.x = position.x / map::PIXELS_IN_METERS;
	box2d.y = position.y / map::PIXELS_IN_METERS;
}

void Position::set(const b2Vec2& position)
{
	sfml.x = position.x * map::PIXELS_IN_METERS;
	sfml.y = position.y * map::PIXELS_IN_METERS;
	box2d.x = position.x;
	box2d.y = position.y;
}

Position& Position::operator= (const b2Vec2& position)
{
	this->set(position);

	return *this;
}

Position& Position::operator= (const sf::Vector2f& position)
{
	this->set(position);

	return *this;
}

Position& Position::move(sf::Vector2f& vector)
{
	this->sfml.x += vector.x;
	this->sfml.y += vector.y;

	this->set(sfml);

	return *this;
}

Position& Position::move(b2Vec2& vector)
{
	this->box2d = vector;
	this->set(box2d);

	return *this;
}

Position& Position::operator+ (const b2Vec2& vector)
{
	this->box2d += vector;
	this->set(box2d);

	return *this;
}

Position& Position::operator+ (const sf::Vector2f& vector)
{
	this->sfml += vector;
	this->set(sfml);

	return *this;
}

Position& Position::operator+ (const float& number)
{
	this->sfml.x += number;
	this->sfml.y += number;
	this->set(sfml);

	return *this;
}

Position& Position::operator- (const b2Vec2& vector)
{
	this->box2d -= vector;
	this->set(box2d);

	return *this;
}

Position& Position::operator- (const sf::Vector2f& vector)
{
	this->sfml -= vector;
	this->set(sfml);

	return *this;
}

Position& Position::operator- (const float& number)
{
	this->sfml.x -= number;
	this->sfml.y -= number;
	this->set(sfml);

	return *this;
}

Position& Position::operator+= (const b2Vec2& vector)
{
	this->box2d += vector;
	this->set(box2d);

	return *this;
}

Position& Position::operator+= (const sf::Vector2f& vector)
{
	this->sfml += vector;
	this->set(sfml);

	return *this;
}

Position& Position::operator+= (const float& number)
{
	this->sfml.x += number;
	this->sfml.y += number;

	this->set(sfml);

	return *this;
}

Position& Position::operator-= (const b2Vec2& vector)
{
	this->box2d -= vector;
	this->set(box2d);

	return *this;
}

Position& Position::operator-= (const sf::Vector2f& vector)
{
	this->sfml -= vector;
	this->set(sfml);

	return *this;
}

Position& Position::operator-= (const float& number)
{
	this->sfml.x -= number;
	this->sfml.y -= number;
	this->set(sfml);

	return *this;
}

Position& Position::operator*= (const b2Vec2& vector)
{
	this->box2d.x *= vector.x;
	this->box2d.y *= vector.y;
	this->set(box2d);

	return *this;
}

Position& Position::operator*= (const sf::Vector2f& vector)
{
	this->sfml.x *= vector.x;
	this->sfml.y *= vector.y;
	this->set(sfml);

	return *this;
}

Position& Position::operator*= (const float& number)
{
	this->sfml.x *= number;
	this->sfml.y *= number;
	this->set(sfml);

	return *this;
}

Position& Position::operator/= (const b2Vec2& vector)
{
	this->box2d.x /= vector.x;
	this->box2d.y /= vector.y;
	this->set(box2d);

	return *this;
}

Position& Position::operator/= (const sf::Vector2f& vector)
{
	this->sfml.x /= vector.x;
	this->sfml.y /= vector.y;
	this->set(sfml);

	return *this;
}

Position& Position::operator/= (const float& number)
{
	this->sfml.x /= number;
	this->sfml.y /= number;
	this->set(sfml);

	return *this;
}


sf::Vector2f Position::getSFPosition()
{
	return this->sfml;
}

b2Vec2 Position::getBox2dPosition()
{
	return this->box2d;
}