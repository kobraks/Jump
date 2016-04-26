#include "Hud.h"

#include "xmlFile.h"

#define MAXLIVES 3

using namespace jump;
using namespace system;

Hud::Hud()
{
	this->_player = NULL;
	this->_points = "0";
	this->_texture = new sf::Texture;
	this->_maxLives = MAXLIVES;

	this->_bar.setFillColor(sf::Color::Color(0, 0, 0, 100));
	this->_bar.setSize(sf::Vector2f(0, 60));
	this->_hearts = NULL;
	this->_numbers = NULL;

	this->_rect = new sf::RectangleShape[this->_maxLives];

	for (int i = 0; i < this->_maxLives; i++)
	{
		this->_rect[i].setSize(sf::Vector2f(40, this->_bar.getSize().y - 20));
		this->_rect[i].setTexture(this->_texture);
	}
}

Hud& Hud::getInstance()
{
	static Hud hud;
	return hud;
}

Hud* Hud::getPointer()
{
	return this;
}

void Hud::draw(sf::RenderWindow& window)
{
	window.draw(this->_bar);

	for (int i = 0; i < this->_maxLives; i++)
	{
		window.draw(this->_rect[i]);
	}

	for (auto element : this->_PointsNumbers)
	{
		window.draw(*element);
	}
}

void Hud::update(sf::RenderWindow& window)
{
	this->_lives = this->_player->getLives();
	this->_points = std::to_string(this->_player->getPoints());

	this->_bar.setSize(sf::Vector2f(window.getSize().x, this->_bar.getSize().y));
	sf::Vector2f coords (window.mapPixelToCoords(sf::Vector2i(0, 0), window.getView()));

	this->_bar.setPosition(coords);

	for (int i = 0; i < this->_maxLives; i++)
	{
		this->_rect[i].setPosition(sf::Vector2f(coords.x + 20 + (i * this->_rect[i].getSize().x), coords.y + (this->_bar.getGlobalBounds().height - this->_rect[i].getGlobalBounds().height) / 2));

		if (i < this->_lives && i >= 0)
		{
			this->_rect[i].setTextureRect(this->_hearts[0]);
		}
		else if (i >= 0)
		{
			this->_rect[i].setTextureRect(this->_hearts[1]);
		}
	}

	if (this->_points.size() > this->_PointsNumbers.size())
	{
		for (int i = this->_PointsNumbers.size(); i < _points.size(); i++)
		{
			this->_PointsNumbers.push_back(new sf::RectangleShape());
			auto tmp = this->_PointsNumbers[this->_PointsNumbers.size()-1];
			tmp->setSize(sf::Vector2f(40, this->_bar.getSize().y - 20));
			tmp->setTexture(this->_texture);
		}
	}

	for (int i = this->_PointsNumbers.size() - 1, o = 0; o < this->_PointsNumbers.size(); i--, o++)
	{
		auto tmp = this->_PointsNumbers[i];
		sf::Vector2f position(coords.x + this->_bar.getSize().x - ( 20 + ((i+1) * tmp->getSize().x)), coords.y + (this->_bar.getGlobalBounds().height - tmp->getGlobalBounds().height) / 2);
		tmp->setPosition(position);
		sf::IntRect rect;
		for (int c = 0; c < 10; c++)
		{
			std::string tmp = std::to_string(c);
			if (tmp[0] == this->_points[o]) rect = this->_numbers[c];
		}

		tmp->setTextureRect(rect);
	}
}

objects::characters::Character* Hud::getPlayer()
{
	return this->_player;
}

void Hud::setPlayer(objects::characters::Character* player)
{
	this->_player = player;
}

sf::Texture* Hud::getTexture()
{
	return this->_texture;
}

Hud::~Hud()
{
	delete[] this->_rect;
	delete[] this->_hearts;
	delete[] this->_numbers;

	for (int i = 0; i < this->_PointsNumbers.size(); i++)
	{
		delete this->_PointsNumbers[i];
	}
	this->_PointsNumbers.clear();

	this->_player = NULL;
	delete this->_texture;
}

void Hud::xml(std::string xmlFIle)
{
	if (this->_hearts) delete this->_hearts;
	if (this->_numbers)  delete this->_numbers;

	auto pos = xmlFIle.rfind('.');
	if (pos != std::string::npos)
	{
		xmlFIle = xmlFIle.substr(0, pos);
	}

	xmlFIle += ".xml";

	this->_hearts = new sf::IntRect[2];

	this->_hearts[0] = xml::getRectFromXMLFile(xmlFIle, "name", "heartFull");
	this->_hearts[1] = xml::getRectFromXMLFile(xmlFIle, "name", "heartEmpty");

	this->_numbers = new sf::IntRect[10];

	for (int i = 0; i < 10; i++)
	{
		this->_numbers[i] = xml::getRectFromXMLFile(xmlFIle, "name", std::to_string(i));
	}
}