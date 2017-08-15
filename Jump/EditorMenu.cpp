#include "EditorMenu.h"
#include "imgui.h"
#include "EntityManager.h"

#include "Entity.h"
#include "EntityManager.h"
#include "GraphicComponent.h"
#include "Log.h"
#include "EntityListCreator.h"
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <limits>

jump::menu::EditorMenu::EditorMenu(Menu* parent): Menu(parent), editor_menu(new Menus)
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

	if (!editor_menu->is_open())
		stop();
}

jump::menu::EditorMenu::Menus::Menus(): show_select_menu_(true), show_edit_entity_menu_(false), show_select_type_entity_menu_(false)
                                        , is_open_(true), selected_(0), entity_(nullptr), entity_list_creator_(new utilities::EntityListCreator())
{
	std::numeric_limits<short> limits;

	buff_size_ = limits.max();
	buff_ = new char[buff_size_];
	buff_[0] = '\0';
}

jump::menu::EditorMenu::Menus::~Menus()
{
	delete entity_list_creator_;
	delete[] buff_;
}

void jump::menu::EditorMenu::Menus::draw()
{
	if (is_open())
	{
		if(show_select_menu_) select_menu(&show_select_menu_);
		if (show_edit_entity_menu_) edit_entity(&show_edit_entity_menu_);
		if (show_select_type_entity_menu_) select_type_of_entity(&show_select_type_entity_menu_);
	}
}

bool jump::menu::EditorMenu::Menus::is_open() const
{
	return is_open_;
}

void jump::menu::EditorMenu::Menus::close()
{
	is_open_ = false;
}

void jump::menu::EditorMenu::Menus::select_menu(bool* p_open)
{
	ImGui::Begin("Select menu", p_open);
	if (ImGui::Button("Edit map"))
	{

	}
	if (ImGui::Button("Edit an entity"))
	{
		show_select_menu_ = false;
		show_edit_entity_menu_ = true;;
	}
	if (ImGui::Button("Back"))
		close();

	ImGui::End();
}

void jump::menu::EditorMenu::Menus::edit_entity(bool* p_open)
{
	entity_list_creator_->update();

	ImGui::Begin("edit entity menu", p_open);
	ImGui::Combo("Entity", reinterpret_cast<int*>(&selected_), entity_list_creator_->get_list() , entity_list_creator_->get_count());
	try
	{
		if (!entity::EntityManager::empty()) entity_ = entity::EntityManager::get_entity(selected_);
	}
	catch(std::exception& ex)
	{
		system::Log::write_error(ex.what());
	}

	if (ImGui::Button("Create New"))
	{
		show_select_type_entity_menu_ = true;
		*p_open = false;
	}
	ImGui::SameLine();
	if (ImGui::Button("Edit entity") && !entity::EntityManager::empty())
	{
		
	}
	ImGui::SameLine();
	if(ImGui::Button("Delete entity"))
	{
		entity::EntityManager::remove_entity(entity_);
	}

	if (ImGui::Button("Back"))
	{
		*p_open = false;
		show_select_menu_ = true;
	}

	ImGui::End();
}

bool jump::menu::EditorMenu::Menus::is_duplicate(char* str)
{
	std::string name(str);

	for(size_t i = 0; i < entity::EntityManager::get_count(); ++i)
		if (entity::EntityManager::get_entity(i)->get_type() == name)
			return true;
	return false;
}

void jump::menu::EditorMenu::Menus::select_type_of_entity(bool* p_open)
{
	ImGui::Begin("Entity name");

	ImGui::InputText("Enter the name", buff_, buff_size_);
	if (ImGui::Button("Accept"))
	{
		std::string entity_name = buff_;
		boost::algorithm::trim(entity_name);
		if (!entity_name.empty())
		{
			if (!is_duplicate(buff_))
			{
				system::Log::write("Create new entity with name: " + entity_name, system::logDEBUG);

				auto entity = new entity::Entity(entity::EntityManager::get_count());
				entity->set_type(entity_name);
				entity::EntityManager::add_entity(entity);
			
				buff_[0] = '\0';

				show_edit_entity_menu_ = true;
				*p_open = false;
			}
			else
				system::Log::write_error("unable to create new entity", "entity name is an duplicate");
		}
		else system::Log::write_error("Unable to create new entity", "Entity must have a name");
	}
	ImGui::SameLine();
	if (ImGui::Button("Cancel"))
	{
		show_edit_entity_menu_ = true;
		*p_open = false;
	}

	ImGui::End();
	
}