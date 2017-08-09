#include "Game.h"

#include "AnimationHandler.h"
#include "BadAllocException.h"
#include "Configuration.h"
#include "defines.h"
#include "FontCoinatiner.h"
#include "GuiManager.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "MainMenu.h"
#include "UnableToLoadFontException.h"
#include "EntityManager.h"

jump::Game::Game(): config_(system::Configuration::get_instance()), menu_(nullptr), time_from_last_update_(sf::Time::Zero)
{
	try
	{
		auto fonts = system::FontCointainer::get_instance();

		fonts->add_font(TITLE_CODE, new sf::Font());
		fonts->add_font(OPTION_CODE, new sf::Font());
		fonts->add_font(AUTHOR_CODE, new sf::Font());
		fonts->add_font(DEBUG_CODE, new sf::Font());

		try
		{
			config_->load(CONFIGURATION_FILE_NAME);
		}
		catch (...)
		{
			config_->set_defaults();
			config_->save(CONFIGURATION_FILE_NAME);
		}

		if (!fonts->get_font(TITLE_CODE)->loadFromFile(config_->font_path + config_->font_names[TITLE_CODE]))
			throw system::exception::UnableToLoadFontException(config_->font_path + config_->font_names[TITLE_CODE]);

		if (!fonts->get_font(OPTION_CODE)->loadFromFile(config_->font_path + config_->font_names[OPTION_CODE]))
			throw system::exception::UnableToLoadFontException(config_->font_path + config_->font_names[OPTION_CODE]);

		if (!fonts->get_font(AUTHOR_CODE)->loadFromFile(config_->font_path + config_->font_names[AUTHOR_CODE]))
			throw system::exception::UnableToLoadFontException(config_->font_path + config_->font_names[AUTHOR_CODE]);

		if (!fonts->get_font(DEBUG_CODE)->loadFromFile(config_->font_path + config_->font_names[DEBUG_CODE]))
			throw system::exception::UnableToLoadFontException(config_->font_path + config_->font_names[DEBUG_CODE]);

		window_ = new sf::RenderWindow(sf::VideoMode(800, 600, 32), WINDOW_NAME, sf::Style::Default);

		system::gui::GuiManager::set_window(*window_);
		ImGui::SFML::Init(*window_);
		menu_ = new menu::MainMenu(*window_);

		try
		{
			entity::EntityManager::load_from_file(ENTITIES_FILE);
		}
		catch(...)
		{ }
	}
	catch (std::bad_alloc)
	{
		throw system::exception::BadAllocException();
	}
}

jump::Game::~Game()
{
	ImGui::SFML::Shutdown();

	if (window_)
		window_->close();

	delete menu_;
	delete window_;
}

void jump::Game::run_game()
{
	auto frame_rate = sf::Time::Zero;
	sf::Clock clock;

	while (window_->isOpen())
	{
		window_->clear();

		parse_events();
		frame_rate = clock.getElapsedTime();
		time_from_last_update_ += clock.getElapsedTime();
		ImGui::SFML::Update(*window_, clock.restart());
		update();

		if (config_->debug)
		{
			auto p_open = true;
			auto mouse_pos = sf::Mouse::getPosition(*window_);

			ImGui::SetNextWindowPos(window_->mapPixelToCoords(sf::Vector2i(0, 0), window_->getView()));
			if (!ImGui::Begin("Example: Fixed Overlay", &p_open, ImVec2(0, 0), 0.3f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
			{
				ImGui::End();
				return;
			}

			ImGui::Text("Fps: %.2f", 1.0f / frame_rate.asSeconds());
			ImGui::Text("Mouse Position: (%i,%i)", mouse_pos.x, mouse_pos.y);
			ImGui::End();
		}

		draw();

		window_->display();
	}
}

void jump::Game::show_frame_rate(bool show, sf::Time tile)
{
	/*	if (show)
		{
			frame_rate_text.setCharacterSize(10U);
			frame_rate_text.setFont(*system::FontCointainer::get_font(DEBUG_CODE));
	
			frame_rate_text.setPosition(window_->mapPixelToCoords(sf::Vector2i(0, 5), window_->getView()));
			frame_rate_text.setString(std::to_string(static_cast<int>(std::truncf(1.0f / frame_rate.asSeconds()))) + " FPS");
	
			window_->draw(frame_rate_text);
		}*/
}

void jump::Game::parse_events()
{
	sf::Event event;

	while (window_->pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);
		menu_->register_event(event);

		if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && sf::Keyboard::Escape == event.key.code)
		{
			if (menu_ && menu_->is_running())
				menu_->stop();
		}
	}
}

void jump::Game::update()
{
	while (time_from_last_update_ >= config_->time_step_)
	{
		time_from_last_update_ -= config_->time_step_;

		system::AnimationHandler::update(*window_);

		if (menu_ && menu_->is_running())
			menu_->update(*window_);
		else
			window_->close();

		menu_->clear_events();
	}
}

void jump::Game::draw()
{
	if (menu_)
		window_->draw(const_cast<sf::Drawable&>(*dynamic_cast<sf::Drawable*>(menu_)));
	//	show_frame_rate(config_->show_fps, clock.getElapsedTime());

	system::AnimationHandler::draw(*window_);
	ImGui::SFML::Render(*window_);
}
