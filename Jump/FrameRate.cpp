#include "FrameRate.h"

#include <cmath>

using namespace jump;
using namespace system;

FrameRate& FrameRate::getInstance()
{
	static FrameRate frame;
	return frame;
}

FrameRate::FrameRate()
{
	clock = NULL;
	text.setCharacterSize(10U);
	text.setPosition(sf::Vector2f(0, 1));
}

void FrameRate::initiate()
{
	if (clock != NULL) delete clock;

	clock = new sf::Clock();
}

FrameRate::FrameRate(sf::Font* debugFont)
{
	text.setFont(*debugFont);
	text.setCharacterSize(1U);
	text.setPosition(sf::Vector2f(0, 10));

	clock = new sf::Clock();
}

FrameRate::~FrameRate()
{
	delete clock;
}

void FrameRate::setFont(sf::Font* font)
{
	this->text.setFont(*font);
}

void FrameRate::setPosition(sf::Vector2f position)
{
	this->text.setPosition(position);
}

sf::Vector2f FrameRate::getPosition()
{
	return text.getPosition();
}

void FrameRate::update()
{
	time = clock->getElapsedTime();
	times = std::to_string((int)std::truncf(1.0f / time.asSeconds()));
	text.setString(times);
	clock->restart();
}

void FrameRate::draw(sf::RenderWindow& window)
{
	window.draw(text);
}
