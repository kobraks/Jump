#include "SplashScreen.h"

#include "AnimationHandler.h"


#include "defines.h"
#include "Configuration.h"

#include "UnableToLoadException.h"
#include "BadAllocException.h"

jump::menu::SplashScreen::SplashScreen(Menu* _parent) : Menu(_parent), scaled_(false)
{
	try
	{
		texture_ = new sf::Texture();

		if (!texture_->loadFromFile(system::Configuration::get_instance()->data_folder + "/" + SFML_LOGO))
			throw system::exception::UnableToLoadException(system::Configuration::get_instance()->data_folder + "/" + SFML_LOGO);

		texture_->setSmooth(true);
		sprite_ = new sf::Sprite();
		sprite_->setTexture(*texture_);

		fade_out_ = new system::animations::FadeOut(*sprite_, 2.5f / 255.f);
		fade_in_ = new system::animations::FadeIn(*sprite_, 2.5f / 255.f);
		fade_in_->run_after_end(fade_out_);
	}
	catch (std::bad_alloc)
	{
		throw system::exception::BadAllocException();
	}
}


jump::menu::SplashScreen::~SplashScreen()
{
	delete texture_;
	delete sprite_;
}

void jump::menu::SplashScreen::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	
}

void jump::menu::SplashScreen::update(sf::Event& _event, sf::RenderWindow& _window)
{
	if (!scaled_)
	{
		scaled_ = true;
		sprite_->setScale(_window.getSize().x / texture_->getSize().x, _window.getSize().y / texture_->getSize().y);
	}

	if (_event.KeyPressed)
	{
		if (fade_in_)
		{
			system::AnimationHandler::remove_animation(fade_in_);
			delete fade_in_;
			fade_in_ = nullptr;
		}
		else if (fade_out_)
		{
			system::AnimationHandler::remove_animation(fade_out_);
			delete fade_out_;
			fade_out_ = nullptr;

			stop();
		}
	}
}
