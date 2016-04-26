#include "Character.h"

using namespace jump;
using namespace objects;
using namespace characters;

Character::Character()
{
	animationStep = 0;
	direction = 0;

	frameCounter = 0;
	switchFrame = 50;
	frameSpeed = 750;

	velocity = sf::Vector2f(0, 0);
}

Character::~Character()
{
}

float Character::getSpeed()
{
	return this->speed;
}

void Character::setSpeed(float speed)
{
	this->speed = speed;
}

Status Character::getStatus()
{
	return this->status;
}

void Character::setStatus(Status status)
{
	this->status = status;
}

sf::Texture& Character::getTexture()
{
	return this->texture;
}

sf::RectangleShape& Character::getRectangle()
{
	return this->rect;
}

sf::Sprite& Character::getSprite()
{
	return this->sprite;
}

b2Body* Character::getBody()
{
	return this->body;
}