#include "Button.h"

Button::Button()
{
	onClick = NULL;
}

Button::~Button()
{
}

void Button::setString(sf::String string)
{
	text.setString(string);

	updateButton();
}

void Button::setCharacterSize(unsigned int size)
{
	text.setCharacterSize(size);

	updateButton();
}

void Button::setFont(sf::Font* font)
{
	text.setFont(*font);

	updateButton();
}

sf::FloatRect Button::getGlobalBounds()
{
	return rectangle.getGlobalBounds();
}

void Button::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x, y));
}

void Button::setPosition(sf::Vector2f position)
{
	rectangle.setPosition(position);

	updateButton();
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(rectangle);
	window.draw(text);
}

void Button::update(sf::Vector2f mouse)
{
	updateButton();

	rectangle.setTexture(&texture);
	rectangle.setTextureRect(sf::IntRect(0, 0, 76, 30));
	text.setColor(sf::Color::Blue);

	if (rectangle.getGlobalBounds().contains(mouse))
	{
		rectangle.setTextureRect(sf::IntRect(152, 0, 76, 30));
		text.setColor(sf::Color::Yellow);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			rectangle.setTextureRect(sf::IntRect(228, 0, 76, 30));
			if (onClick != NULL) (*onClick)();
		}
	}
}

sf::Vector2f Button::getPosition()
{
	return this->rectangle.getPosition();
}

bool Button::loadFromFIle(std::string fileName)
{
	bool tmp = texture.loadFromFile(fileName);
	texture.setSmooth(true);
	return tmp;
}

void Button::setActionOnClick(void(*onClick)())
{
	this->onClick = onClick;
	return;
}

void Button::updateButton()
{
	rectangle.setSize(sf::Vector2f(text.getGlobalBounds().width + 20, text.getGlobalBounds().height + 20));
	text.setPosition(sf::Vector2f(rectangle.getPosition().x + 10, rectangle.getPosition().y));
}