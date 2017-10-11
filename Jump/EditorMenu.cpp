#include "EditorMenu.h"
#include "imgui.h"
#include "EntityManager.h"

#include "Entity.h"
#include "EntityManager.h"
#include "GraphicComponent.h"
#include "Log.h"
#include "EntityListCreator.h"
#include "EditorMsgs.h"

#include "GuiButton.h"
#include "GuiForm.h"
#include "GuiComboBox.h"
#include "GuiMenu.h"
#include "GuiMenuBar.h"
#include "GuiMenuItem.h"
#include "Configuration.h"
#include "GuiManager.h"

jump::menu::EditorMenu::EditorMenu(Menu* parent): Menu(parent)
{
	using namespace system::gui;

	form_ = new GuiForm(nullptr, "Editor menu", sf::Vector2f(0,0), sf::Vector2f(800, 500));
	form_->set_flags(GUI_NO_SAVE);
	GuiMenuBar* menu_bar = new GuiMenuBar();
	auto file_menu = new GuiMenu(menu_bar, "File");

	file_menu->add(new GuiMenuItem(file_menu, "open", ""));
	file_menu->name();

	GuiMenu* entity_menu = new GuiMenu(menu_bar, "Entity");
	
	menu_bar->add(file_menu);
	menu_bar->add(entity_menu);

	file_menu->name();


	form_->add(menu_bar);

	file_menu->name();


	GuiManager::add(form_);

	file_menu->name();

}

jump::menu::EditorMenu::~EditorMenu()
{
	system::gui::GuiManager::remove_and_destroy(form_);
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