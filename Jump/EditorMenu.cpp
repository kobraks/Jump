#include "EditorMenu.h"
#include "imgui.h"
#include "EntityManager.h"

#include "Entity.h"
#include "EntityManager.h"
#include "GraphicComponent.h"
#include "Log.h"
#include "EntityListCreator.h"
#include "EditorMsgs.h"

#include "GuiManager.h"
#include "Configuration.h"
#include "GuiInputMessageBox.h"
#include "GuiMenuSeparator.h"
#include "EntityLoader.h"

#include "BadAllocException.h"
#include "NotInicializedException.h"
#include "SceneWriter.h"
#include "SceneLoader.h"

jump::menu::EditorMenu::EditorMenu(Menu* parent): Menu(parent)
{
	using namespace system::gui;
	input_ = nullptr;
	scene_manager_ = nullptr;

	try
	{
		form_ = new GuiForm(nullptr, "Editor menu", sf::Vector2f(0, 0), sf::Vector2f(800, 500));
		form_->set_flags(GUI_NO_SAVE);
		GuiMenuBar* menu_bar = new GuiMenuBar();
		auto file_menu = new GuiMenu(menu_bar, "File");

		file_menu->add(new GuiMenuItem(file_menu, "open", "CTRL+O", [this](GuiItem*) { open_button(); }));

		save_ = new GuiMenuItem(file_menu, "save", "CTRL+S", [this](GuiItem* item) { save_button(item); });
		save_->enabled(false);

		save_as_ = new GuiMenuItem(file_menu, "save as", "CTRL+ALT+S", [this](GuiItem* item) { save_button(item); });

		file_menu->add(new GuiMenuSeparator());

		file_menu->add(save_);
		file_menu->add(save_as_);


		GuiMenu* entity_menu = new GuiMenu(menu_bar, "Entity");

		menu_bar->add(file_menu);
		menu_bar->add(entity_menu);

		form_->add(menu_bar);

		GuiManager::add(form_);
	}
	catch (std::bad_alloc)
	{
		throw system::exception::BadAllocException();
	}
}

jump::menu::EditorMenu::~EditorMenu()
{
	system::gui::GuiManager::remove_and_destroy(form_);
	delete scene_manager_;
	delete input_;
}

void jump::menu::EditorMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void jump::menu::EditorMenu::update(sf::RenderWindow& window)
{
	if (!is_running()) return;

	if (!system::gui::GuiManager::exist(form_))
		stop();
}

void jump::menu::EditorMenu::load_scene(const std::string& file_name)
{
	try
	{
		if (scene_manager_)
		{
			delete scene_manager_;
			scene_manager_ = nullptr;
		}

		scene_manager_ = new scene::SceneManager();

		//auto loader = new scene::SceneLoader(scene_manager_, file_name);

		//delete loader;
	}
	catch (std::bad_alloc)
	{
		throw system::exception::BadAllocException();
	}
}

void jump::menu::EditorMenu::save_scene(const std::string& file_name)
{
	if (!scene_manager_)
		throw system::exception::NotInicializedException();

	save_->enabled(true);
	current_scene_name_ = file_name;

	try
	{
		//auto writer = new scene::SceneWriter(scene_manager_, file_name);

		//delete writer;
	}
	catch (std::bad_alloc)
	{
		throw system::exception::BadAllocException();
	}
}

void jump::menu::EditorMenu::open_button()
{
	system::Log::write("Clicked open", system::logDEBUG4);

	input_ = new system::gui::GuiInputMessageBox(form_, " ", "File name");
	input_->set_action_on_close([this](system::gui::GuiItem*)
	{
		load_scene(input_->writed_text()); 
		delete input_; 
		input_ = nullptr;
	});
}

void jump::menu::EditorMenu::save_button(system::gui::GuiItem* item)
{
	if (item == save_)
	{
		if(!current_scene_name_.empty())
			save_scene(current_scene_name_);
	}
	else if (item == save_as_)
	{
		if (input_) delete input_;
		input_ = new system::gui::GuiInputMessageBox(form_, " ", "File_name");
		input_->set_action_on_close([this](system::gui::GuiItem*)
		{
			save_scene(input_->writed_text());
			delete input_;
			input_ = nullptr;
		});
	}
}
