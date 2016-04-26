#pragma once

#include <SFML\Graphics.hpp>

#include "Exports.h"

class GUIMenager;

class Item
{
public:
	GUI_INTERFACE virtual sf::FloatRect getGlobalBounds() = 0;
	GUI_INTERFACE virtual void draw(sf::RenderWindow &window) = 0;
	GUI_INTERFACE virtual void update(sf::Vector2f mouse) = 0;

	friend GUIMenager;
};

