#pragma once

#include <SFML\Graphics.hpp>
#include <string>

#include "Exports.h"
#include "Item.h"

class Button:
	public Item
{
public:
	GUI_INTERFACE Button();
	GUI_INTERFACE ~Button();

	GUI_INTERFACE void setString(sf::String string);
	GUI_INTERFACE void setFont(sf::Font *font);
	GUI_INTERFACE void setCharacterSize(unsigned int size);
	GUI_INTERFACE void setPosition(sf::Vector2f position);
	GUI_INTERFACE void setPosition(float x, float y);

	GUI_INTERFACE bool loadFromFIle(std::string name);

	GUI_INTERFACE virtual sf::FloatRect getGlobalBounds();

	GUI_INTERFACE sf::Vector2f getPosition();

	GUI_INTERFACE void setActionOnClick(void(*onClick)());
private:
	sf::RectangleShape rectangle;
	sf::Text text;

	void updateButton();

	virtual void draw(sf::RenderWindow& window);
	virtual void update(sf::Vector2f mouse);
	sf::Texture texture;

	void(*onClick)();
};

