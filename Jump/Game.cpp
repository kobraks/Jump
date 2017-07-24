#include "Game.h"
#include <iostream>

#include "UnableToLoadException.h"
#include "UnableToLoadFontException.h"
#include "BadAllocException.h"

#include "GuiManager.h"
#include "GuiItem.h"
#include "GuiButton.h"
#include "FrameRate.h"

#include "defines.h"
#include "FontCoinatiner.h"

#include "AnimationHandler.h"

#include "MainMenu.h"

jump::Game::Game(): menu_(nullptr)
{
	try
	{
		auto fonts = system::FontCointainer::get_instance();
		auto config = system::Configuration::get_instance();

		fonts->add_font(TITLE_CODE, new sf::Font());
		fonts->add_font(OPTION_CODE, new sf::Font());
		fonts->add_font(AUTHOR_CODE, new sf::Font());
		fonts->add_font(DEBUG_CODE, new sf::Font());

		try
		{
			config->load(CONFIGURATION_FILE_NAME);
		}
		catch (...)
		{
			config->set_defaults();
			config->save(CONFIGURATION_FILE_NAME);
		}

		if (fonts->get_font(TITLE_CODE)->loadFromFile(config->font_path + config->font_names[TITLE_CODE]))
			throw system::exception::UnableToLoadFontException(config->font_path + config->font_names[TITLE_CODE]);

		if (fonts->get_font(OPTION_CODE)->loadFromFile(config->font_path + config->font_names[OPTION_CODE]))
			throw system::exception::UnableToLoadFontException(config->font_path + config->font_names[OPTION_CODE]);

		if (fonts->get_font(AUTHOR_CODE)->loadFromFile(config->font_path + config->font_names[AUTHOR_CODE]))
			throw system::exception::UnableToLoadFontException(config->font_path + config->font_names[AUTHOR_CODE]);

		if (fonts->get_font(DEBUG_CODE)->loadFromFile(config->font_path + config->font_names[DEBUG_CODE]))
			throw system::exception::UnableToLoadFontException(config->font_path + config->font_names[DEBUG_CODE]);

		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;

		window_ = new sf::RenderWindow(sf::VideoMode(800, 600, 32), WINDOW_NAME, sf::Style::Default, settings);
		system::gui::GuiManager::set_window(*window_);

		mouse_position_.setCharacterSize(20u);
		mouse_position_.setFont(*system::FontCointainer::get_font(DEBUG_CODE));
	}
	catch(std::bad_alloc)
	{
		throw system::exception::BadAllocException();
	}
}

jump::Game::~Game()
{
	if(window_)
		window_->close();

	for (auto it = menu_; it != nullptr; it = menu_->parent())
	{
		auto parent = menu_->parent();
		delete menu_;
		menu_ = parent;
	}

	delete window_;	
}

void jump::Game::run_game()
{
	menu_ = new menu::MainMenu(*window_);
	system::Configuration* config = system::Configuration::get_instance();

	sf::Time time_from_last_update = sf::Time::Zero;
	sf::Clock clock;

	if (config->show_fps)
	{
		system::FrameRate::getInstance().setFont(system::FontCointainer::get_font(DEBUG_CODE));
		system::FrameRate::getInstance().initiate();
	}

	while (window_->isOpen() || menu_)
	{
		time_from_last_update += clock.restart();
		window_->clear();

		sf::Vector2f mouse(sf::Mouse::getPosition(*window_));
		sf::Event event;

		while (window_->pollEvent(event))
		{
			menu_->add_event(event);

			//Wciœniêcie ESC lub przycisk X
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && sf::Keyboard::Escape == event.key.code)
			{
				if (menu_ && menu_->is_running())
					menu_->stop();
			}
		}

		if (config->debug)
		{
			mouse_position_.setPosition(window_->mapPixelToCoords(sf::Vector2i(10, 10), window_->getView()));
			auto text = "x: " + std::to_string(mouse.x) + " y: " + std::to_string(mouse.y);

			mouse_position_.setString(text);
		}

		while (time_from_last_update >= config->time_step_)
		{
			time_from_last_update -= config->time_step_;

			update();
		}

		window_->clear();
		draw();
		window_->display();
	}
}

void jump::Game::update()
{
	system::AnimationHandler::update(*window_);

	if (menu_ && menu_->is_running())
		menu_->update(*window_);
	else
		window_->close();
}

void jump::Game::draw()
{
	system::AnimationHandler::draw(*window_);
	if (menu_)
		window_->draw(const_cast<sf::Drawable&>(*dynamic_cast<sf::Drawable*>(menu_)));
}