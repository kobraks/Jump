#include "Engine.h"

#include <iostream>
#include <algorithm>
#include <codecvt>
//#include <thread>
//#include <mutex>

#include "Character.h"
#include "FrameRate.h"
#include "Box2D\Box2D.h"
#include "Log.h"
#include "Hud.h"

//TODO poprawiæ kod update, frameRate.

//std::mutex m;

using namespace jump;

Engine::Engine(system::Configuration* config)
{
	this->config = config;
	this->map = new map::Map(config);
	this->player = new objects::characters::Player(config);
	player->LoadTextureFromFile(config->texturesPath + config->playerTextures);
}


Engine::~Engine()
{
	config = NULL;

	delete player;
	delete config;
	delete map;
}

void Engine::runEngine(sf::RenderWindow* window)
{
	window->setView(sf::View(window->getDefaultView()));
	game = true;

	std::string tmp = [](std::wstring w)->std::string {
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
		return convert.to_bytes(w);
	}(config->startMap);

	map->LoadFromFile(tmp, window);
	player->setPosition(map->getStartPosition());
	player->create(map->getWorld());
	system::Hud::getInstance().setPlayer(this->player);
	system::Hud::getInstance().getTexture()->loadFromFile(config->texturesPath + config->hudTextures);
	system::Hud::getInstance().xml(config->xmlFiles + config->hudTextures);

	if (config->debug)
	{
		playerSpeed.setFont(*config->debugFont);
		playerSpeed.setCharacterSize(20);
	}

	FILE_LOG(logDEBUG3) << "Create cllision listener";
	map->getWorld()->SetContactListener(this);	
}

void Engine::update(sf::Time timeStep, sf::RenderWindow* window)
{
	//m.lock();
	if (config->debug)
	{
		sf::Vector2f coords(window->mapPixelToCoords(sf::Vector2i(0, 0), window->getView()));

		playerSpeed.setPosition(coords);
		playerSpeed.setString("Actualy speed: " + std::to_string(player->getSpeed()));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) && config->debug)
	{
		player->setSpeed(player->getSpeed() + 1.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) && config->debug)
	{
		player->setSpeed(player->getSpeed() - 1.f);
	}
	
	map->update(timeStep, player, *window);
	player->update(timeStep, map);
	system::Hud::getInstance().update(*window);

	this->destroyBody();
	//m.unlock();
}

void Engine::destroyBody()
{
	/*for (auto element : this->toRemove)
	{
		if (element)
		{
			switch (element->type)
			{
			case map::Type::ITEM:
				objects::other::Items* item = (objects::other::Items*) element->pointer;
				map->getWorld()->DestroyBody(item->getBody());

				this->map->getItems().erase(this->map->getItems().begin() + item->getNumber());

				delete item;
				delete element;
				element = NULL;

				break;
			}
		}
	}*/


	if (this->toRemove.empty()) return;

	std::vector<Remover*> removed;
	while (!this->toRemove.empty())
	{
		auto element = this->toRemove.front();
		this->toRemove.pop();

		bool can = true;

		if (!removed.empty())
		{
			for (auto e : removed)
			{
				if (element->pointer == e->pointer) can = false;
			}
		}

		if (can)
		{
			removed.push_back(element);

			switch (element->type)
			{
			case map::Type::ITEM:
				objects::other::Items* item = (objects::other::Items*) element->pointer;
				map->getWorld()->DestroyBody(item->getBody());

				this->map->getItems().erase(this->map->getItems().begin() + item->getNumber());
				break;
			}
		}
	}

	for (auto element : removed)
	{
		switch (element->type)
		{
		case map::Type::ITEM:
			delete (objects::other::Items*)element->pointer;
			break;
		}
		element->pointer = NULL;
		delete element;
	}
	removed.clear();

	/*auto it = std::unique(this->toRemove.begin(), this->toRemove.end(), [](Remover* a, Remover* b)->bool { return a->pointer == b->pointer; });
	this->toRemove.resize(std::distance(this->toRemove.begin(), it));

	for (int i = 0; i < toRemove.size(); i++)
	{
		auto element = this->toRemove[i];

		if (element)
		{
			switch (element->type)
			{
			case map::Type::ITEM:
				objects::other::Items* item = (objects::other::Items*) element->pointer;
				map->getWorld()->DestroyBody(item->getBody());

				this->map->getItems().erase(this->map->getItems().begin() + item->getNumber());
				
				delete item;
				delete element;
				this->toRemove[i] = NULL;

				break;
			}
		}
	}

	toRemove.clear();*/
}

void Engine::draw(sf::RenderWindow& window)
{
	// Wyœwietlanie na ekranie

	map->draw(window);
	player->draw(window);
	sf::Vector2f coords(window.mapPixelToCoords(sf::Vector2i(0, 1), window.getView()));
	system::FrameRate::getInstance().setPosition(coords);
	if (config->debug) window.draw(playerSpeed);

	system::Hud::getInstance().draw(window);
	system::FrameRate::getInstance().draw(window);
	//std::cout << FrameRate::getInstance() << std::endl;
}

void Engine::reload(sf::RenderWindow* window)
{
	map->getWorld()->DestroyBody(player->getBody());

	map->LoadFromFile(map->fileName, window);
	player->create(map->getWorld());
	player->setPosition(map->getStartPosition());
	system::Hud::getInstance().setPlayer(this->player);
	system::Hud::getInstance().getTexture()->loadFromFile(config->texturesPath + config->hudTextures);
	system::Hud::getInstance().xml(config->xmlFiles + config->hudTextures);

	map->getWorld()->SetContactListener(this);
}

void Engine::BeginContact(b2Contact* contact)
{
	int typeFixA = (int)contact->GetFixtureA()->GetUserData();
	int typeFixB = (int)contact->GetFixtureB()->GetUserData();

	FILE_LOG(logDEBUG4) << "contact\n"
		<< "typeFixA " << typeFixA << " " << (int)contact->GetFixtureA()->GetBody()->GetUserData() << std::endl
		<< "typeFIxB " << typeFixB << " " << (int)contact->GetFixtureB()->GetBody()->GetUserData();

	if ((int)contact->GetFixtureA()->GetBody()->GetUserData() == map::Type::PLAYER)
	{
		if (typeFixA == map::Type::PLAYER_FOOT_SENSOR ||
		typeFixA == map::Type::PLAYER_HEAD_SENSOR)
		{
			typeFixB = (int)contact->GetFixtureB()->GetBody()->GetUserData();

			player->contact(static_cast<map::Type>(typeFixA), static_cast<map::Type>(typeFixB));
		}
	}
	else if ((int)contact->GetFixtureB()->GetBody()->GetUserData() == map::Type::PLAYER)
	{
		if (typeFixB == map::Type::PLAYER_FOOT_SENSOR ||
			typeFixB == map::Type::PLAYER_HEAD_SENSOR)
		{
			typeFixA = (int)contact->GetFixtureA()->GetBody()->GetUserData();

			player->contact(static_cast<map::Type>(typeFixB), static_cast<map::Type>(typeFixA));
		}
		else if (typeFixA == map::Type::ITEM)
		{
			objects::other::Items* item = (objects::other::Items*)contact->GetFixtureA()->GetBody()->GetUserData();
			int tmpLives = player->getLives();

			player->contact(static_cast<map::Type>(typeFixB), static_cast<map::Type>(typeFixA), contact->GetFixtureA()->GetBody());
			if (item->getType() != objects::other::Items::SPIKES)
			{
				if (item->getType() == objects::other::Items::Type::HEART && tmpLives < 3)
				{
					this->toRemove.push(new Remover((void*)item, map::Type::ITEM));
				}
				else if (item->getType() != objects::other::Items::Type::HEART)
				{
					this->toRemove.push(new Remover((void*)item, map::Type::ITEM));
				}
			}
		}
	}

}

void Engine::EndContact(b2Contact* contact)
{
	int typeFixA = (int)contact->GetFixtureA()->GetUserData();
	int typeFixB = (int)contact->GetFixtureB()->GetUserData();

	FILE_LOG(logDEBUG4) << "end contact \n"
		<< "typeFixA " << typeFixA << " " << (int)contact->GetFixtureA()->GetBody()->GetUserData() << std::endl
		<< "typeFIxB " << typeFixB << " " << (int)contact->GetFixtureB()->GetBody()->GetUserData();

	if ((int)contact->GetFixtureA()->GetBody()->GetUserData() == map::Type::PLAYER)
	{
		if (typeFixA == map::Type::PLAYER_FOOT_SENSOR ||
			typeFixA == map::Type::PLAYER_HEAD_SENSOR)
		{
			typeFixB = (int)contact->GetFixtureB()->GetBody()->GetUserData();

			player->endContact(static_cast<map::Type>(typeFixA), static_cast<map::Type>(typeFixB));
		}
		else if (typeFixB == map::Type::ITEM)
		{
			typeFixB = (int)contact->GetFixtureB()->GetBody()->GetUserData();

			player->endContact(static_cast<map::Type>(typeFixA), static_cast<map::Type>(typeFixB));
		}
	}
	else if ((int)contact->GetFixtureA()->GetBody()->GetUserData() == map::Type::ENEMY)
	{

	}

	if ((int)contact->GetFixtureB()->GetBody()->GetUserData() == map::Type::PLAYER)
	{
		if (typeFixB == map::Type::PLAYER_FOOT_SENSOR ||
			typeFixB == map::Type::PLAYER_HEAD_SENSOR)
		{
			typeFixA = (int)contact->GetFixtureA()->GetBody()->GetUserData();

			player->endContact(static_cast<map::Type>(typeFixB), static_cast<map::Type>(typeFixA));
		}
		else if (typeFixB == map::Type::ITEM)
		{
			typeFixA = (int)contact->GetFixtureA()->GetBody()->GetUserData();

			player->endContact(static_cast<map::Type>(typeFixB), static_cast<map::Type>(typeFixA));
		}
	}
	else if ((int)contact->GetFixtureB()->GetBody()->GetUserData() == map::Type::ENEMY)
	{

	}

}

Engine::Remover::Remover(void* pointer, map::Type type)
{
	this->pointer = pointer;
	this->type = type;
}