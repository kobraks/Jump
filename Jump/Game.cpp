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
#include "Log.h"
#include "Console.h"

#include "GuiMessageBox.h"

jump::Game::Game(): config_(system::Configuration::get_instance()), time_from_last_update_(sf::Time::Zero), show_log_(false), show_console_(false), menu_(nullptr)
{
	try
	{
		auto log = system::Log::get_instance();
		auto fonts = system::FontCointainer::get_instance();

		fonts->add_font(TITLE_CODE, new sf::Font());
		fonts->add_font(OPTION_CODE, new sf::Font());
		fonts->add_font(AUTHOR_CODE, new sf::Font());
		fonts->add_font(DEBUG_CODE, new sf::Font());

		try
		{
			log->write("Load configuration file");
			config_->load(CONFIGURATION_FILE_NAME);
		}
		catch (std::exception& ex)
		{
			log->write_error("Unable to open configuration file attempt to create new file", ex.what());
			config_->set_defaults();
			try
			{
				config_->save(CONFIGURATION_FILE_NAME);
			}
			catch (std::exception& exception)
			{
				log->write_error("Unabe to save configuration file", exception.what());
			}
		}

		log->write("start to load fonts");
		log->write("attempt to load font: " + config_->font_path + config_->font_names[TITLE_CODE]);
		if (!fonts->get_font(TITLE_CODE)->loadFromFile(config_->font_path + config_->font_names[TITLE_CODE]))
		{
			log->write_error("Unable to load font", MSG_UNABLE_TO_LOAD_FONT + config_->font_path + config_->font_names[TITLE_CODE]);
			throw system::exception::UnableToLoadFontException(config_->font_path + config_->font_names[TITLE_CODE]);
		}

		log->write("attempt to load font: " + config_->font_path + config_->font_names[OPTION_CODE]);
		if (!fonts->get_font(OPTION_CODE)->loadFromFile(config_->font_path + config_->font_names[OPTION_CODE]))
		{
			log->write_error("Unable to load font", MSG_UNABLE_TO_LOAD_FONT + config_->font_path + config_->font_names[OPTION_CODE]);
			throw system::exception::UnableToLoadFontException(config_->font_path + config_->font_names[OPTION_CODE]);
		}

		log->write("attempt to load font: " + config_->font_path + config_->font_names[AUTHOR_CODE]);
		if (!fonts->get_font(AUTHOR_CODE)->loadFromFile(config_->font_path + config_->font_names[AUTHOR_CODE]))
		{
			log->write_error("Unable to load font", MSG_UNABLE_TO_LOAD_FONT + config_->font_path + config_->font_names[OPTION_CODE]);
			throw system::exception::UnableToLoadFontException(config_->font_path + config_->font_names[AUTHOR_CODE]);
		}

		log->write("attempt to load font: " + config_->font_path + config_->font_names[DEBUG_CODE]);
		if (!fonts->get_font(DEBUG_CODE)->loadFromFile(config_->font_path + config_->font_names[DEBUG_CODE]))
		{
			log->write_error("Unable to load font", MSG_UNABLE_TO_LOAD_FONT + config_->font_path + config_->font_names[DEBUG_CODE]);
			throw system::exception::UnableToLoadFontException(config_->font_path + config_->font_names[DEBUG_CODE]);
		}

		try
		{
			log->write("Attempt to load entities");
			entity::EntityManager::load_from_file(ENTITIES_FILE);
		}
		catch (std::exception& ex)
		{
			log->write_error("Unable to load entities", ex.what());
		}

		log->write("creating window: ");
		window_ = new sf::RenderWindow(sf::VideoMode(800, 600, 32), WINDOW_NAME, sf::Style::Default);

		system::gui::GuiManager::set_window(*window_);
		ImGui::SFML::Init(*window_);
		menu_ = new menu::MainMenu(*window_);
	}
	catch (std::bad_alloc& ex)
	{
		system::Log::write_error("Unable to alocate more memory", ex.what());
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
	system::gui::GuiMessageBox message_box(nullptr, "ala", "beata", system::gui::YES_NO_IGNORE_BUTTON);


	while (window_->isOpen())
	{
		window_->clear();

		parse_events();
		frame_rate = clock.getElapsedTime();
		time_from_last_update_ += clock.getElapsedTime();
		ImGui::SFML::Update(*window_, clock.restart());
		update();

		//ImGui::ShowTestWindow();

		draw();

		if (config_->debug || config_->show_fps)
		{
			auto p_open = true;
			auto mouse_pos = sf::Mouse::getPosition(*window_);

			ImGui::SetNextWindowPos(window_->mapPixelToCoords(sf::Vector2i(0, 0), window_->getView()));
			if (!ImGui::Begin("Fixed Overlay", &p_open, ImVec2(0, 0), 0.3f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::End();
				return;
			}

			ImGui::Text("Fps: %.2f", 1.0f / frame_rate.asSeconds());

			if (config_->debug)
			{
				ImGui::Text("Mouse Position: (%i,%i)", mouse_pos.x, mouse_pos.y);
			}
			ImGui::End();
		}
		ImGui::SFML::Render(*window_);


		window_->display();
	}

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

		if (config_->debug)
		{
			if (event.type == event.KeyReleased && event.key.code == sf::Keyboard::F3)
			{
				show_log_ = !show_log_;
			}

			if (event.type == event.KeyReleased && event.key.code == sf::Keyboard::Tilde)
			{
				show_console_ = !show_console_;
			}
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
	system::gui::GuiManager::draw();
	
	if (menu_)
		window_->draw(const_cast<sf::Drawable&>(*dynamic_cast<sf::Drawable*>(menu_)));

	system::AnimationHandler::draw(*window_);
	if (show_log_) system::Log::draw("Log", &show_log_);
	if (show_console_) system::Console::draw("Console", &show_console_);
}
