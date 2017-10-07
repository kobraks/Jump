#include "MainMenu.h"

#include "GuiManager.h"

#include "Configuration.h"
#include "FontCoinatiner.h"

#include "BadAllocException.h"

#include "SplashScreen.h"
#include "EditorMenu.h"
#include "Log.h"


jump::menu::MainMenu::MainMenu(sf::RenderWindow& _window, Menu* _parent) : Menu(_parent)
{
	try
	{
		menu_ = new SplashScreen(_window, this);
		texture_button_ = nullptr;

/*		const size_t amount_options = 3;
		std::string options[] =
		{
			START_GAME,
			OPTIONS,
			EXIT
		};

		std::vector<system::gui::GuiItem*> buttons;

		for (int i = 0; i < amount_options; i++)
		{
			auto button = new system::gui::GuiButton(options[i], *system::FontCointainer::get_font(OPTION_CODE));

			button->set_character_size(50U);
			if (!texture_button_->loadFromFile(system::Configuration::get_instance()->interface_path + "/" + BUTTON_TEXUTRE))
				throw system::exception::UnableToLoadException(system::Configuration::get_instance()->interface_path + "/" + BUTTON_TEXUTRE);

			button->position(_window.getSize().x / 2 - button->size().x / 2,
				_window.getSize().y / 2 - (((button->size().y + 30) * amount_options / 2))
				+ (button->size().y + 5) * i);

			button->set_texture_normal(texture_button_, sf::IntRect(0, 0, 76, 30));
			button->set_texture_hovered(texture_button_, sf::IntRect(152, 0, 76, 30));
			button->set_texture_clicked(texture_button_, sf::IntRect(228, 0, 76, 30));

			switch (i)
			{
			case 0:
				button->add_action_on_click([this](sf::Event&, system::gui::GuiItem*) { menu_ = nullptr; });
				break;

			case 1:
				button->add_action_on_click([this](sf::Event&, system::gui::GuiItem*) { menu_ = nullptr; });
				break;

			case 2:
				button->add_action_on_click([this](sf::Event&, system::gui::GuiItem*) { menu_ = nullptr; });
				break;
			}

			buttons.push_back(button);
		}

		system::gui::GuiManager::add(buttons.begin(), buttons.end());*/
	}
	catch(std::bad_alloc)
	{
		throw system::exception::BadAllocException();
	}
}


jump::menu::MainMenu::~MainMenu()
{
	delete menu_;
	system::gui::GuiManager::clear();
	delete texture_button_;
}

void jump::menu::MainMenu::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	if (menu_)
		_target.draw(const_cast<sf::Drawable&>(*dynamic_cast<sf::Drawable*>(menu_)), _states);
}

void jump::menu::MainMenu::update(sf::RenderWindow& window)
{
	auto events = get_events();

	while(!events.empty())
	{
		auto event = events.front();
		events.pop();

		if (system::Configuration::get_instance()->debug)
		{
			if (event.type == event.KeyReleased && event.key.code == sf::Keyboard::F2)
			{
				if (!dynamic_cast<EditorMenu*>(menu_))
				{
					delete menu_;
					menu_ = new EditorMenu(this);
				}
				else
				{
					delete menu_;
					menu_ = nullptr;
				}
			}
		}
		
	}

	if (menu_)
	{
		if (!menu_->is_running())
		{
			delete menu_;
			menu_ = nullptr;
		}
		else
			menu_->update(window);
	}
}
