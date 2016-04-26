#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include <list>

#include "Exports.h"
#include "Item.h"

class GUIMenager
{
public:
	GUI_INTERFACE ~GUIMenager();

	GUI_INTERFACE static GUIMenager& getInstance();

	GUI_INTERFACE GUIMenager& add(std::vector<Item*>& items);
	GUI_INTERFACE GUIMenager& add(Item* item);

	GUI_INTERFACE GUIMenager& draw(sf::RenderWindow& window);
	GUI_INTERFACE GUIMenager& update(sf::Vector2f mouse);

	GUI_INTERFACE std::vector<Item* >& getItems();
	GUI_INTERFACE GUIMenager& clear();
private:
	GUIMenager();
	GUIMenager(const GUIMenager&);

	std::list<Item*> items;
};

