#pragma once
#include "Menu.h"

#include "GuiButton.h"
#include "GuiForm.h"
#include "GuiComboBox.h"
#include "GuiMenu.h"
#include "GuiMenuBar.h"
#include "GuiMenuItem.h"
#include "GuiInputMessageBox.h"
#include "SceneManager.h"

namespace jump
{
	namespace entity
	{
		class Entity;
	}

	namespace utilities
	{
		class EntityListCreator;
	}

	namespace menu
	{
		class EditorMenu : public Menu
		{
		public:
			explicit EditorMenu(Menu* parent);
			~EditorMenu();

			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			void update(sf::RenderWindow& window) override;

			void load_scene(const std::string& file_name);
			void save_scene(const std::string& file_name);
		protected:
			void open_button();
			void save_button(system::gui::GuiItem* item);

		private:			
			system::gui::GuiForm* form_;
			system::gui::GuiMenuItem* save_,* save_as_;

			system::gui::GuiInputMessageBox* input_;
			scene::SceneManager* scene_manager_;

			std::string current_scene_name_;
		};
	}
}

