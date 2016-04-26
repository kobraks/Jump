#include "Bust.h"

using namespace jump;
using namespace system;

Bust::Bust()
{
	clock = NULL;
	time = 120;
	_isStarted = false;
	type = NONE;
}


Bust::~Bust()
{
	stop();
}

void Bust::start(Bust::Type type)
{
	clock = new sf::Clock();
}

void Bust::stop()
{
	delete clock;
	_isStarted = false;
}

void Bust::update(sf::RenderWindow* window)
{
	if (window)
	{
		//TODO
	}

	if (_isStarted)
	{
		if (clock->getElapsedTime().asSeconds() >= time)
		{
			stop();
		}
	}
}

void Bust::setTime(float time)
{
	this->time = time;
}

float Bust::getTime()
{
	return this->time;
}

void Bust::setType(Type type)
{
	this->type = type;
}

Bust::Type Bust::getType()
{
	return this->type;
}

bool Bust::isStarted()
{
	return this->_isStarted;
}