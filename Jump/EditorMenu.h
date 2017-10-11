#pragma once
#include "Menu.h"

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

	namespace system
	{
		namespace gui
		{
			class GuiForm;
			class GuiMessageBox;
			class GuiLabel;
			class GuiMenuBar;
			class GuiMenu;
			class GuiMenuItem;
			class GuiComboBox;
		}
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

		private:			
			system::gui::GuiForm* form_;
		};
	}
}

