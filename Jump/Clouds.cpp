#include "Clouds.h"

#include <RapidXml\rapidxml.hpp>
#include <memory>
#include <boost\algorithm\string.hpp>
#include <iostream>
#include <thread>
#include <chrono>

#include "xmlFile.h"
#include "Log.h"

using namespace jump;
using namespace objects;
using namespace other;

#pragma region Clouds

Clouds::Clouds(system::Configuration* config, sf::Vector2f spawnTime, sf::Vector2f speed, bool to_left, bool to_right)
{
	this->_config = config;
	this->_time = spawnTime;
	this->_speed = speed;

	if (to_left) this->_direction = LEFT;
	if (to_right) this->_direction = RIGHT;

	this->_texture = NULL;
	this->_clock = new sf::Clock();
	this->_maxClouds = config->maxClouds;
	this->_cloudsTextures = 0;

	this->_createTime = this->rand(spawnTime.x, spawnTime.y);
}


Clouds::~Clouds()
{
	delete _clock;
	_texture = NULL;
	delete _texture;

	_config = NULL;
	delete _config;;

	for (int i = 0; i < this->_clouds.size(); i++)
	{
		delete this->_clouds[i];
	}

	this->_clouds.clear();
}

void Clouds::draw(sf::RenderWindow& window)
{
	if (!this->_clouds.empty())
	{
		for (auto cloud : this->_clouds)
		{
			cloud->draw(window);
		}
	}
}

void Clouds::update(float time, sf::RenderWindow& window)
{
	sf::View view = window.getView();

	std::vector <int> toRemove;

	sf::FloatRect screen(sf::Vector2f(view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2)), sf::Vector2f(view.getSize().x, view.getSize().y));
	create(screen);

	screen.width += 140;
	screen.left -= 70;

	for (int i = 0; i < this->_clouds.size(); i++)
	{
		if (!this->_clouds[i]->getSpirte().getGlobalBounds().intersects(screen))
		{
			toRemove.push_back(i);
		}
		else
		{
			this->_clouds[i]->move(time);
		}
	}

	if (!toRemove.empty())
	{
		for (int i = 0; i < toRemove.size(); i++)
		{
			delete this->_clouds[toRemove[i] - i];
			this->_clouds.erase(this->_clouds.begin() + (toRemove[i] - i));
		}
	}
}

void Clouds::create(sf::FloatRect screen)
{
	if (this->_clock->getElapsedTime().asSeconds() >= this->_createTime)
	{
		this->_clock->restart();
		this->_createTime = this->rand(this->_time.x, this->_time.y);

		if (!this->_texture) return;
		if (this->_clouds.size() > this->_maxClouds) return;

		FILE_LOG(logINFO) << "Create Cloud";

		float speed = this->rand(this->_speed.x, this->_speed.y);

		this->_clouds.push_back(new Cloud(speed, _direction));
		auto cloud = this->_clouds[this->_clouds.size() - 1];

		sf::IntRect rect;

		std::string name = "cloud";
		std::string number = std::to_string((int)this->rand(0, this->_cloudsTextures));

		if (number == "0") number.clear();

		name += number;
		rect = system::xml::getRectFromXMLFile(_xmlFile, "name", name);

		cloud->getSpirte().setTexture(*this->_texture);
		cloud->getSpirte().setTextureRect(rect);
		cloud->setSize(sf::Vector2f(this->rand(60, 300), this->rand(35, 200)));
		
		float x = this->_direction == LEFT ? screen.left + screen.width : screen.width - screen.left;

		cloud->getSpirte().setPosition(sf::Vector2f(x, this->rand(-80, 25)));
	}	
}

float Clouds::rand(float min, float max)
{
	if (min > max)
	{
		float tmp = max;
		max = min;
		min = tmp;
	}

	static thread_local std::mt19937_64 generator (static_cast<uint64_t> (std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())));
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

void Clouds::loadTextureFromFile(std::string fileName, std::string xmlFile)
{
	this->_texture = new sf::Texture();
	this->_texture->loadFromFile(fileName);

	this->_xmlFile = xmlFile;

	std::string name = "cloud";

	std::auto_ptr<char> fileContent(system::xml::fileToChar(xmlFile));

	rapidxml::xml_document <> document;

	try
	{
		document.parse <0>(fileContent.get());
	}
	catch (rapidxml::parse_error er)
	{
		FILE_LOG(logERROR) << er.what();
	}

	rapidxml::xml_node <>* root = document.first_node();

	for (auto node = root->first_node(); node; node = node->next_sibling())
	{
		for (auto atribe = node->first_attribute(); atribe; atribe = atribe->next_attribute())
		{
			std::string attribeName = atribe->name();

			if (boost::to_upper_copy(attribeName) == boost::to_upper_copy(std::string("name")))
			{
				std::string value = atribe->value();
				auto pos = value.find(name);

				if (pos != std::string::npos) this->_cloudsTextures++;
			}
		}
	}

	document.clear();
}

#pragma endregion

#pragma region Cloud

Clouds::Cloud::Cloud(float speed, Clouds::Direction direction)
{
	this->_direction = direction;
	this->_speed = speed;
}

Clouds::Direction Clouds::Cloud::getDirection()
{
	return this->_direction;
}

void Clouds::Cloud::setDirection(Clouds::Direction direction)
{
	this->_direction = direction;
}

sf::Sprite& Clouds::Cloud::getSpirte()
{
	return this->_sprite;
}

void Clouds::Cloud::move(float time)
{
	sf::Vector2f velocity(1, 0);

	velocity.x *= time * this->_speed;

	if (this->_direction == Clouds::Direction::LEFT) velocity.x *= -1;

	this->_sprite.move(velocity);
}

void Clouds::Cloud::draw(sf::RenderWindow& window)
{
	window.draw(this->_sprite);
}

void Clouds::Cloud::setSize(float x, float y)
{
	this->setSize(sf::Vector2f(x, y));
}

void Clouds::Cloud::setSize(sf::Vector2f size)
{
	this->_sprite.setScale(size.x / this->_sprite.getTextureRect().width, size.y / this->_sprite.getTextureRect().height);
}

#pragma endregion