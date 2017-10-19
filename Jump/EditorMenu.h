#pragma once
#include "Menu.h"

#include "GuiButton.h"
#include "GuiForm.h"
#include "GuiComboBox.h"
#include "GuiMenu.h"
#include "GuiMenuBar.h"
#include "GuiMenuItem.h"

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

		protected:
			void open_button();

		private:			
			system::gui::GuiForm* form_;
		};
	}
}

