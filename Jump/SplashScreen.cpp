#include "SplashScreen.h"

#include "AnimationHandler.h"


#include "defines.h"
#include "Configuration.h"

#include "UnableToLoadException.h"
#include "BadAllocException.h"

jump::menu::SplashScreen::SplashScreen(sf::RenderWindow& window, Menu* _parent) : Menu(_parent)
{
	try
	{
		texture_ = new sf::Texture();

		if (!texture_->loadFromFile(system::Configuration::get_instance()->data_folder + "/" + SFML_LOGO))
			throw system::exception::UnableToLoadException(system::Configuration::get_instance()->data_folder + "/" + SFML_LOGO);

		texture_->setSmooth(true);
		sprite_ = new sf::Sprite();
		sprite_->setTexture(*texture_);
		sprite_->setScale(static_cast<float>(window.getSize().x) / texture_->getSize().x, static_cast<float>(window.getSize().y) / texture_->getSize().y);

		fade_out_ = new system::animations::FadeOut(*sprite_, 2.5f / 255.f);
		fade_in_ = new system::animations::FadeIn(*sprite_, 2.5f / 255.f);
		fade_in_->run_after_end(fade_out_);

		system::AnimationHandler::add(fade_in_);
	}
	catch (std::bad_alloc)
	{
		throw system::exception::BadAllocException();
	}
}


jump::menu::SplashScreen::~SplashScreen()
{
	try
	{
		system::AnimationHandler::remove_animation(fade_in_);
	}
	catch(...) {}

	try
	{
		system::AnimationHandler::remove_animation(fade_out_);
	}
	catch(...){}

	fade_in_ = fade_out_ = nullptr;

	delete texture_;
	delete sprite_;
}

void jump::menu::SplashScreen::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
}

void jump::menu::SplashScreen::update(sf::RenderWindow& window)
{
	if (!is_running())
		return;

	auto events = get_events();
	while(!events.empty())
	{
		auto event = events.front();
		events.pop();

		if (event.type == sf::Event::Resized)
		{
			sprite_->setScale(static_cast<float>(window.getSize().x) / texture_->getSize().x, static_cast<float>(window.getSize().y) / texture_->getSize().y);
		}

		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
		{
			if (fade_in_)
			{
				try
				{
					system::AnimationHandler::remove_animation(fade_in_);
				}
				catch (...)
				{
				}
				fade_in_ = nullptr;
			}
			else
			{
				try
				{
					system::AnimationHandler::remove_animation(fade_out_);
				}
				catch (...)
				{
				}

				fade_out_ = nullptr;
				stop();
			}
		}
	}

	if (fade_in_)
		if (!system::AnimationHandler::contains(fade_in_))
			fade_in_ = nullptr;

	if (fade_out_)
		if (!system::AnimationHandler::contains(fade_out_))
		{
			fade_out_ = nullptr;
			stop();
		}
}
