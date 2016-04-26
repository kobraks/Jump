#include "Game.h"
#include <iostream>

#include "GUIMenager.h"
#include "Item.h"
#include "Button.h"
#include "FrameRate.h"

#include "AnimationHandler.h"
#include "FadeIn.h"
#include "FadeOut.h"

using namespace jump;

const sf::Time timeStep = sf::seconds(1.f / 60.f);

Game::Game()
{
	titleFont = new sf::Font();
	optionsFont = new sf::Font();
	authorFont = new sf::Font();
	debugFont = new sf::Font();
	
	config = new system::Configuration();
	config->loadFromFile(L"configuration.ini");

	if (!titleFont->loadFromFile(config->fontPath + config->fontNames["title"]) ||
		!optionsFont->loadFromFile(config->fontPath + config->fontNames["options"]) ||
		!authorFont->loadFromFile(config->fontPath + config->fontNames["author"]) ||
		!debugFont->loadFromFile(config->fontPath + config->fontNames["debug"]))
	{

		FILE_LOG(logERROR) << "Cannot load font";

		MessageBox(NULL, L"Cannot load font", L"Cannot load font", MB_YESNOCANCEL);
		return;
	}

	config->debugFont = debugFont;
	config->font = optionsFont;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	FILE_LOG(logINFO) << "Initialize window";
	window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Jump", sf::Style::Default, settings);
	FILE_LOG(logINFO) << "Initialize engine";
	engine = NULL;

	state = SPLASCHSCREEN;
}

Game::~Game()
{
	delete engine;

	delete window;
	delete titleFont;
	delete authorFont;
	delete optionsFont;
}

void Game::runGame()
{
	splaschScreen(config->dataFile + "/sfml-logo.png");

	sf::Time timefromlastupdate = sf::Time::Zero;
	sf::Clock clock;

	if (config->showFPS)
	{
		system::FrameRate::getInstance().setFont(config->debugFont);
		system::FrameRate::getInstance().initiate();
	}

	while (window->isOpen())
	{
		timefromlastupdate += clock.restart();
		window->clear();

		sf::Vector2f mouse(sf::Mouse::getPosition(*window));
		sf::Event event;

		while (window->pollEvent(event))
		{
			//Wci�ni�cie ESC lub przycisk X
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Escape && state == MENU)
				state = EXIT;

			if (event.key.code == sf::Keyboard::Escape && state == SPLASCHSCREEN)
			{
				auto animations = system::AnimationHandler::getInstance().getAnimations();

				for (auto element : animations)
				{
					if (element->isRunning() && !element->isPaused())
					{
						element->stop();
						break;
					}
				}
			}

			if (event.key.code == sf::Keyboard::F5 && state == GAME)
			{
				if (this->engine) engine->reload(window);
			}
		}

		if (config->debug)
		{
			std::string text;
			text = "x: " + std::to_string(mouse.x);
			text += " y: " + std::to_string(mouse.y);

			mousePosition.setString(text);
		}

		while (timefromlastupdate >= timeStep)
		{
			timefromlastupdate -= timeStep;

			update();
		}

		window->clear();
		draw();
		window->display();
	}
}

Game::GameState states;

void Game::update()
{
	system::AnimationHandler::getInstance().update();

	switch (state)
	{
	case SPLASCHSCREEN:

		if (system::AnimationHandler::getInstance().getAnimations().empty())
		{
			state = MENU;
			createMenu();
		}
		break;
	case MENU:
		GUIMenager::getInstance().update(sf::Vector2f(sf::Mouse::getPosition(*window)));
		
		if (state != states)
		{
			GUIMenager::getInstance().clear();
		}
		state = states;

		break;

	case GAME:
		if (!engine)
		{
			engine = new Engine(config);
			engine->runEngine(window);
		}
		engine->update(timeStep, window);

		break;

	case EXIT:
		window->close();
		break;
	}
}

void Game::draw()
{
	system::AnimationHandler::getInstance().draw(*window);

	switch (state)
	{
	case MENU:
		GUIMenager::getInstance().draw(*window);

	case GAME:
		if (engine) engine->draw(*window);
	}

	if (config->debug) window->draw(mousePosition);
	if (config->showFPS)
	{
		system::FrameRate::getInstance().update();
		system::FrameRate::getInstance().draw(*window);
	}
}

void Game::createMenu()
{
	states = state;

	amoutOptions = 3;
	optionsNames = new std::wstring[amoutOptions];

	optionsNames[0] = L"Start Gry";
	optionsNames[1] = L"Opcje";
	optionsNames[2] = L"Wyjscie";

	std::vector<Item*> buttons;

	std::cout << window->getSize().x << std::endl;
	std::cout << window->getSize().y << std::endl;

	for (int i = 0; i < amoutOptions; i++)
	{
		Button* button = new Button;

		button->setFont(this->optionsFont);
		button->setString(optionsNames[i]);
		button->setCharacterSize(50U);
		button->loadFromFIle(config->dataFile + "/Interface/button.png");

		button->setPosition(window->getSize().x / 2 - button->getGlobalBounds().width / 2,
			window->getSize().y / 2 - (((button->getGlobalBounds().height + 30)* amoutOptions / 2))
			+ (button->getGlobalBounds().height + 5) * i);

		switch (i)
		{
		case 0:
			button->setActionOnClick([]()->void {states = GAME; });
			break;

		case 1:
			button->setActionOnClick([]()->void {states = OPTIONS; });
			break;

		case 2:
			button->setActionOnClick([]()->void {states = EXIT; });
			break;
		}

		buttons.push_back(button);
	}

	mousePosition.setPosition(sf::Vector2f(10, 10));
	mousePosition.setCharacterSize(20u);
	mousePosition.setFont(*debugFont);

	GUIMenager::getInstance().add(buttons);
}

void Game::splaschScreen(std::string fileName)
{
	sf::Texture texture;
	texture.loadFromFile(fileName);
	texture.setSmooth(true);

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(window->getSize().x / texture.getSize().x, window->getSize().y / texture.getSize().y);

	system::Animation* animation = new system::animations::FadeIn(sprite, 2.5/255.f);

	system::AnimationHandler::getInstance().addAnimation(animation, new system::animations::FadeOut(sprite, 2.5 / 255.f));
}