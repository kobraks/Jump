#include "EditorMenu.h"
#include "imgui.h"
#include "EntityManager.h"

jump::menu::EditorMenu::EditorMenu(Menu* parent): Menu(parent), state_(state::SELECT_MENU), editor_menu(new Menus)
{
}


jump::menu::EditorMenu::~EditorMenu()
{
}

void jump::menu::EditorMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	editor_menu->draw();
}

void jump::menu::EditorMenu::update(sf::RenderWindow& window)
{
	if (!is_running()) return;

	if (editor_menu->get_state() == state::EXIT_MENU)
		stop();

	
}

jump::menu::EditorMenu::Menus::Menus(): state_(state::SELECT_MENU)
{
}

jump::menu::EditorMenu::Menus::~Menus()
{
}

sf::Uint8 jump::menu::EditorMenu::Menus::get_state() const
{
	return state_;
}

void jump::menu::EditorMenu::Menus::set_state(sf::Uint8 state)
{
	state_ = state;
}

void jump::menu::EditorMenu::Menus::draw()
{
	switch (state_)
	{
	case state::EXIT_MENU:
		break;
	case state::SELECT_MENU:
		select_menu();
		break;
	case state::CREATE_ENTITY_MENU: 
		create_entity();
		break;
	default:;
	}
}

void jump::menu::EditorMenu::Menus::create_entity()
{
	static auto item = 1;

	ImGui::Begin("Entity Creator");
	ImGui::Combo("", &item, "");
	if (ImGui::Button("back"))
		state_ = state::SELECT_MENU;
	ImGui::End();
}

void jump::menu::EditorMenu::Menus::select_menu()
{
	ImGui::Begin("Select menu");
	if (ImGui::Button("Edit map"))
	{
		state_ = state::EDIT_MAP_MENU;
	}
	if (ImGui::Button("Create map"))
	{
		state_ = state::CREATE_MAP_MENU;
	}
	if (ImGui::Button("Edit an entity"))
	{
		state_ = state::EDIT_ENTITY_MENU;
	}
	if (ImGui::Button("Create an entity"))
	{
		state_ = state::CREATE_ENTITY_MENU;
	}
	if (ImGui::Button("Back"))
	{
		state_ = state::EXIT_MENU;
	}

	ImGui::End();
}
