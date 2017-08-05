#include "EditorMenu.h"
#include "imgui.h"
#include "EntityManager.h"

jump::menu::EditorMenu::EditorMenu(Menu* parent): Menu(parent), state_(state::SELECT_MENU)
{
}


jump::menu::EditorMenu::~EditorMenu()
{
}

void jump::menu::EditorMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void jump::menu::EditorMenu::update(const sf::Event& _event, sf::RenderWindow& _window)
{
}

void jump::menu::EditorMenu::update(sf::RenderWindow& window)
{
	switch (state_)
	{
	case state::EXIT_MENU:
		stop();
		break;
	case state::SELECT_MENU:
		select_menu();
		break;
	case state::CREATE_ENTITY_MENU: break;
	default: ;
	}
}

void jump::menu::EditorMenu::create_entity()
{
}

void jump::menu::EditorMenu::select_menu()
{
	ImGui::Begin("Select menu");
	if (ImGui::Button("Create map"))
	{
		
	}
	if (ImGui::Button("Edit an entity"))
	{
		
	}
	if (ImGui::Button("Create an entity"))
	{
		state_ = state::CREATE_ENTITY_MENU;
	}

	ImGui::End();
}
