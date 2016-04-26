#include "GUIMenager.h"

#include <algorithm>

GUIMenager& GUIMenager::getInstance()
{
	static GUIMenager instance;

	return instance;
}

GUIMenager::GUIMenager()
{
}


GUIMenager::~GUIMenager()
{
	clear();
}

GUIMenager& GUIMenager::add(std::vector<Item*>& items)
{
	for (int i = 0; i < items.size(); i++)
	{
		this->items.push_back(items[i]);
	}

	return *this;
}

GUIMenager& GUIMenager::add(Item* item)
{
	items.push_back(item);

	return *this;
}

GUIMenager& GUIMenager::draw(sf::RenderWindow& window)
{
	for (auto element : items)
	{
		element->draw(window);
	}

	return *this;
}

GUIMenager& GUIMenager::update(sf::Vector2f mouse)
{
	for (auto element : items)
	{
		element->update(mouse);
	}

	return *this;
}

std::vector <Item* >& GUIMenager::getItems()
{
	std::vector <Item*> temp;
	for (auto element : items)
	{
		temp.push_back(element);
	}

	return temp;
}

GUIMenager& GUIMenager::clear()
{
	for (auto element : items)
	{
		delete element;
	}

	items.clear();
	return *this;
}