#include "Map.h"

#include <iostream>
#include <cmath>
#include <windows.h>

#include <boost\algorithm\string.hpp>
#include <codecvt>

#include "Loading.h"
#include "Log.h"
#include "xmlFile.h"

namespace jump
{
	namespace map
	{
		inline void change(float& f, float& s)
		{
			float tmp = f;
			f = s;
			s = f;
		}

		struct PositionMinMax
		{
			sf::Vector2f min, max;
		};

		PositionMinMax getPosition(mapf::MapFiles* map, std::wstring& line)
		{
			PositionMinMax tmp;

			if (!map->exist(line + L"x") && !map->exist(line + L"y")) return tmp;

			std::wstring valuex = map->getValue(line + L"x");
			std::wstring valuey = map->getValue(line + L"y");

			auto posx = valuex.find(L':');
			auto posy = valuey.find(L':');

			if (posx != std::string::npos)
			{
				tmp.min.x = std::stoi(valuex.substr(0, posx));
				tmp.max.x = std::stoi(valuex.substr(posx + 1));
			}
			else
			{
				tmp.min.x = std::stoi(valuex.substr(0, posx));
				tmp.max.x = tmp.min.x;
			}

			if (posy != std::string::npos)
			{
				tmp.min.y = std::stoi(valuey.substr(0, posy));
				tmp.max.y = std::stoi(valuey.substr(posy + 1));
			}
			else
			{
				tmp.min.y = std::stoi(valuey.substr(0, posy));
				tmp.max.y = tmp.min.y;
			}

			if (tmp.min.x > tmp.max.x)
			{
				change(tmp.min.x, tmp.max.x);
			}

			if (tmp.min.y > tmp.max.y)
			{
				change(tmp.min.y, tmp.min.y);
			}

			return tmp;
		}
	}
}

using namespace jump;
using namespace map;
using namespace system::xml;

Map::Map(system::Configuration* config)
{
	this->config = config;
	height = 0;
	width = 0;
	groundHeight = 0;
	gravity = 1.0f;

	viewStartPosition = sf::Vector2f(0, 0);
	world = NULL;
	cloud = NULL;
}

Map::~Map()
{
	clear();

	config = NULL;
	delete config;
}

void Map::clear()
{
	for (int i = 0; i < items.size(); i++)
	{
		//this->world->DestroyBody(items[i]->getBody());

		delete items[i];
	}

	delete world;
	delete cloud;
	
	items.clear();

	cloud = NULL;
}

b2World* Map::getWorld()
{
	return this->world;
}

bool Map::LoadFromFile(std::string name, sf::RenderWindow* window)
{
	if (world)
	{
		clear();
	}


	this->fileName = name;

	system::Loading::getInstance().loadTextureFromFile(config->loadingTextures);
	system::Loading::getInstance().initialize(config->font);
	system::Loading::getInstance().start(window);

	mapf::MapFiles map;
	map.open(name);

	system::Loading::getInstance().add();

	if (!map.good())
	{
		system::Loading::getInstance().stop();
		return false;
	}

	this->name = map[L"map.name"];

	//pobieranie rozmiarów mapy
	if (map.exist(L"map.width"))
	{
		int width = map.getInt(L"map.width");
		this->width = width < 0? width * (-1) : width;
	}
	else if (map.exist(L"map.size.x"))
	{
		int width = map.getInt(L"map.size.x");
		this->width = width < 0 ? width * (-1) : width;
	}
	else this->width = 0;

	if (map.exist(L"map.height"))
	{
		int height = map.getInt(L"map.height");
		this->height = height < 0 ? height * (-1) : height;
	}
	else if (map.exist(L"map.size.y"))
	{
		int height = map.getInt(L"map.size.y");
		this->height = height < 0 ? height * (-1) : height;
	}
	else this->height = 0;

	system::Loading::getInstance().add();

	//Pobieranie rozmiaru jedneg bloku
	if (map.exist(L"map.tailwidth"))
	{
		int width = map.getInt(L"map.tailwidth");
		this->tailSize.x = width < 0 ? width * (-1) : width;
	}
	else if (map.exist(L"map.tail.x"))
	{
		int width = map.getInt(L"map.tail.x");
		this->tailSize.x = width < 0 ? width * (-1) : width;
	}
	else tailSize.x = 0;

	if (map.exist(L"map.tailheight"))
	{
		int height = map.getInt(L"map.tailheight");
		this->tailSize.y = height < 0 ? height * (-1) : height;
	}
	else if (map.exist(L"map.tail.y"))
	{
		int height = map.getInt(L"map.tail.y");
		this->tailSize.y = height < 0 ? height * (-1) : height;
	}
	else this->tailSize.y = 0;

	//Pobieranie grawitacji
	if (map.exist(L"map.gravity"))
	{
		float gravity = map.getFloat(L"map.gravity");
		this->gravity = gravity < 0 ? gravity * (-1) : gravity;
	}
	else this->gravity = 400.0f;

	system::Loading::getInstance().add();

	if (map.exist(L"map.groundHeight"))
	{
		int ground = map.getInt(L"map.groundHeight");
		this->groundHeight = ground < 0 ? -ground : ground;
	}
	else
		this->groundHeight = tailSize.y * height + 64;

	//Pobieranie pozycji startowej
	if (map.exist(L"map.startPosition.x"))
	{
		int start = map.getInt(L"map.startPosition.x");
		startPosition.x = start < 0 ? -start : start;
	}
	else	startPosition.x = 0;

	if (map.exist(L"map.startPosition.y"))
	{
		int start = map.getInt(L"map.startPosition.y");
		startPosition.y = start < 0 ? -start: start;
	}
	else	startPosition.y = 0;

	//Pobranie pozycji wyjœcia z mapy
	if (map.exist(L"map.endposition.x"))
	{
		int end = map.getInt(L"map.endposition.x");
		endPosition.x = end < 0 ? -end : end;
	}
	else endPosition.x = width - 1;
	
	if (map.exist(L"map.endposition.y"))
	{
		int end = map.getInt(L"map.endposition.y");
		endPosition.y = end < 0 ? -end : end;
	}
	else endPosition.y = -1;
	
	if (map.exist(L"map.endposition.nextmap"))
	{
		this->nextMap = map[L"map.endposition.nextmap"];
	}
	else
	{
		nextMap.clear();
	}

	if (!this->texture.loadFromFile(config->texturesPath + map["map.texture"]))
	{
		//if (!config->debug)
		{
			MessageBox(NULL, L"Cannot load texture", L"Cannot load texture", MB_OK | MB_ICONERROR);
		}

	}

	system::Loading::getInstance().add();

	if (map.exist(L"map.background.fileName"))
	{
		this->bacgroundTexture.loadFromFile(config->texturesPath + map.getValue("map.background.fileName"));
	}
	else if (map.exist(L"map.background.number"))
	{
		int number = map.getInt(L"map.background.number");
		this->bacgroundTexture.loadFromImage(texture.copyToImage(), getRectFromXMLFile(config->xmlFiles + map["map.texture"], "number", std::to_string(number + 1)));
	}
	else if (map.exist(L"map.background.name"))
	{
		std::string textureName = map.getValue("map.background.name");
		this->bacgroundTexture.loadFromImage(texture.copyToImage(), getRectFromXMLFile(config->xmlFiles + map["map.texture"], "name", textureName));
	}

	if (map.exist(L"map.clouds.have_clouds"))
	{
		if (map.getBool(L"map.clouds.have_clouds"))
		{
			sf::Vector2f time(5, 120);
			bool left = true;
			sf::Vector2f speed(50, 200);
		
			if (map.exist(L"map.clouds.timeToSpawn.min"))
			{
				time.x = map.getFloat(L"map.clouds.timeToSpawn.min");
			}

			if (map.exist("map.clouds.timeToSpawn.max"))
			{
				time.y = map.getFloat("map.clouds.timeToSpawn.max");
			}

			if (map.exist(L"map.clouds.to_left"))
			{
				left = map.getBool("map.clouds.to_left");
			}
			else left = false;

			if (map.exist(L"map.clouds.speed.min"))
			{
				speed.x = map.getFloat("map.clouds.speed.min");
			}

			if (map.exist(L"map.clouds.speed.max"))
			{
				speed.y = map.getFloat("map.clouds.speed.max");
			}

			this->cloud = new objects::other::Clouds(config, time, speed, left, !left);

			std::string file = config->texturesPath + config->itemsTextures;
			std::string xml = config->xmlFiles + config->itemsTextures;

			auto pos = xml.find('.');
			if (pos != std::string::npos)
			{
				xml = xml.substr(0, pos);
			}
			xml += ".xml";

			this->cloud->loadTextureFromFile(file, xml);
		}
	}

	rect.setTexture(&this->bacgroundTexture);

	system::Loading::getInstance().add();

	std::string tmp;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
	tmp = convert.to_bytes(this->name);

	int size = map.getSize();
	FILE_LOG(logINFO) << "Create Map";
	FILE_LOG(logINFO) << "Map name: " << tmp << " size(x: " << this->width << " y: " << this->height << ")  gravityForce:" << getGravityForce();
	FILE_LOG(logINFO) << "Create physics";
	FILE_LOG(logINFO) << "Create World";

	this->world = new b2World(b2Vec2(0, gravity));

	for (int i = 1; i < size; i++)
	{
		system::Loading::getInstance().add(((i * 100)) / system::Loading::getInstance().getValue());

		if (map.exist(std::to_string(i) + ".enemy.isEnemy"))
		{
			
		}
		else if (map.exist(std::to_string(i) + ".item.isItem"))
		{
			createItem(i, map);
		}
		else
		{
			createTials(i, map);
		}
	}

	system::Loading::getInstance().add();


	system::Loading::getInstance().stop();
	return true;
}

#pragma region create

void Map::createItem(int i, mapf::MapFiles& map)
{
	std::wstring o = std::to_wstring(i) + L".";
	int value = -1;

	if (map.exist(o + L"item.isItem"))
	{
		std::wstring type = map.getValue(o + L"item.type");

		if (objects::other::Items::getTypeFromWString(type) != objects::other::Items::Type::NONE)
		{
			if (map.exist(o + L"item.value")) value = map.getInt(o + L"item.value");
			auto pos = getPosition(&map, o);

			for (int x = pos.min.x; x <= pos.max.x; x++)
			{
				for (int y = pos.min.y; y <= pos.max.y; y++)
				{
					int itemNumber = items.size();
					this->items.push_back(new objects::other::Items(itemNumber, objects::other::Items::getTypeFromWString(type)));
					auto item = (objects::other::Items*) this->items[this->items.size() - 1];

					item->setSize(tailSize);
					item->setPosition(x, y);
					item->setValue(value);
					item->createBody(this->world);

					item->loadTextureFromFile(config->texturesPath, config->itemsTextures, config->xmlFiles);
				}
			}
		}

	}
	else return;
}

void Map::createTials(int i, mapf::MapFiles& map)
{
	sf::Vector2f min, max;

	bool isWall = true;
	bool display = true;
	bool isMoving = false;
	sf::Vector2f min2 = sf::Vector2f(0, 0);
	sf::Vector2f max2 = sf::Vector2f(0, 0);
	int number = 0, movingSpeed = 50;
	std::string textureName;
	std::wstring o = std::to_wstring(i) + L".";
	sf::IntRect rect;

	if (map.exist(o + L"moving.can_move"))
	{
		isMoving = map.getBool(o + L"moving.can_move");

		if (isMoving)
		{
			std::wstring valuex = map[o + L"moving.x"];
			std::wstring valuey = map[o + L"moving.y"];

			auto posx = valuex.find(L':');
			auto posy = valuey.find(L':');

			if (posx != std::string::npos)
			{
				min2.x = std::stoi(valuex.substr(0, posx));
				max2.x = std::stoi(valuex.substr(posx + 1));

				if (min2.x > max2.x) change(min2.x, max2.x);
				else if (min2.x == max2.x)
				{
					min2.x = 0;
					max2.x = 0;
				}
			}
			else 
			{
				min2.x = 0;
				max2.x = 0;
			}

			if (posy != std::string::npos)
			{
				min2.y = std::stoi(valuey.substr(0, posy));
				max2.y = std::stoi(valuey.substr(posy + 1));

				if (min2.y > max2.y) change(min2.y, max2.y);
				else if (min2.y == max2.y)
				{
					min2.y = 0;
					max2.y = 0;
				}
			}
			else
			{
				min2.y = 0;
				max2.y = 0;
			}

			if (map.exist(o + L"moving.speed"))
			{
				movingSpeed = map.getInt(o + L"moving.speed");
			}
		}
	}

	if (map.exist(o + L"have_collision"))
		isWall = map.getBool(o + L"have_collision");

	if (map.exist(o + L"display"))
		display = map.getBool(o + L"display");

	if (map.exist(o + L"number"))
		number = map.getInt(o + L"number");
	else if (map.exist(o + L"name"))
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
		textureName = convert.to_bytes(map.getValue(o + L"name"));
	}

	if (map.exist(o + L"water"))
	{
		if (map.getBool(o + L"water"))
		{
			display = false;
			isWall = false;

		}
	}

	if (textureName.empty()) rect = getRectFromXMLFile(config->xmlFiles + map["map.texture"], "number", std::to_string(number + 1));
	else rect = getRectFromXMLFile(config->xmlFiles + map["map.texture"], "name", textureName);

	auto pos = getPosition(&map, o);
	min = pos.min;
	max = pos.max;

	int maxTails = (max.x - min.x) > 0 ? max.x - min.x : 1;
	maxTails += (max.y - min.y) > 0 ? max.y - max.y : 1;

	for (int i = 0; i < maxTails; i++)
	{
		if (!display && !isWall) break;

		for (uint mx = min.x; mx <= max.x; mx++)
		{
			if (mx > width) break;

			for (uint my = min.y; my <= max.y; my++)
			{
				if (my > height) break;

				items.push_back(new map::Tail());

				auto tail = (Tail*)items[items.size() - 1];

				tail->setPosition(sf::Vector2f(mx, my));
				tail->display(display);
				tail->isWall(isWall);
				tail->setNumber(number);

				tail->moving(isMoving);
				if (tail->moving())
				{
					tail->setMoveMax(max2);
					tail->setMoveMin(min2);
					tail->setSpeed(movingSpeed);
				}

				if (tail->isWall())
				{
					tail->createBody(this->world);
				}

				if (tail->display())
				{
					tail->getSprite().setTexture(texture);
					tail->getSprite().setTextureRect(rect);
				}

				tail->setSize(tailSize);
			}
		}
	}
}

#pragma endregion

std::vector<Tile*>& Map::getItems()
{
	return items;
}

void Map::SaveToFile(std::string name)
{
	//TODO
}

sf::Vector2f Map::getStartPosition()
{
	return this->startPosition;
}

unsigned int Map::getGroundPosition()
{
	return this->groundHeight;
}

void Map::draw(sf::RenderWindow& window)
{
	sf::View view = window.getView();
	sf::FloatRect screen = sf::FloatRect(sf::Vector2f(view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2)), view.getSize());
	
	sf::Vector2f coords(window.mapPixelToCoords(sf::Vector2i(0, 0), view));
	this->rect.setPosition(coords);
	this->rect.setSize(view.getSize());

	window.draw(this->rect);

	if (cloud) cloud->draw(window);

	if (!items.empty())
	{
		for (auto item : items)
		{
			if (item)
			{
				sf::FloatRect collider(item->getGlobalBounds());

				if (collider.intersects(screen))
				{
					item->draw(window);
				}
			}
		}
	}

	/*for (auto tail : tails)
	{
		if (tail->getSprite().getGlobalBounds().intersects(screen))
		{
			tail->draw(window, config->debug);
		}
	}*/
}

float Map::getGravityForce()
{
	return this->gravity;
}

void Map::updatePlatforms(sf::Time timeStep, sf::FloatRect screen)
{
	for (auto tail : items)
	{
		if (((Tail*)tail)->moving())
		{
			sf::Vector2f velocity = sf::Vector2f(1.0f, 1.0f);
			tail->move(timeStep.asSeconds(), velocity);
		}
	}
}

void Map::update(sf::Time time, objects::characters::Character* player, sf::RenderWindow& window)
{
	this->world->Step(time.asSeconds(), 8, 3);

	if (cloud) cloud->update(time.asSeconds(), window);

	sf::Vector2f playerPosition = player->getRectangle().getPosition();
	int speed = player->getSpeed();

	this->updatePlatforms(time, sf::FloatRect(sf::Vector2f(window.getView().getCenter().x - (window.getView().getSize().x / 2), window.getView().getCenter().y - (window.getView().getSize().y / 2)), window.getView().getSize()));

	auto view = window.getView();

	if (viewStartPosition.x == 0 && viewStartPosition.y == 0) viewStartPosition = view.getCenter();

	if (playerPosition.x >= view.getCenter().x)
	{
		view.move(sf::Vector2f(1 * time.asSeconds() * speed, 0));
	}
	else if (playerPosition.x < view.getCenter().x - 32)
	{
		if (viewStartPosition.x != view.getCenter().x)
		view.move(sf::Vector2f(-1 * time.asSeconds() * speed, 0));
	}

	if (playerPosition.y <= view.getCenter().y)
	{
		view.move(sf::Vector2f(0, -1 * time.asSeconds() * speed));
	}
	else if (playerPosition.y > view.getCenter().y + 64 && view.getCenter().y < viewStartPosition.y)
	{
		if (viewStartPosition.y != view.getCenter().y)
		view.move(sf::Vector2f(0, 1 * time.asSeconds() * speed));
	}

	window.setView(view);
}