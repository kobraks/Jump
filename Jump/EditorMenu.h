#pragma once
#include "Menu.h"

namespace jump
{
	namespace menu
	{
		namespace state
		{
			const sf::Uint8 EXIT_MENU = 0x00;
			const sf::Uint8 SELECT_MENU = 0x01;
			const sf::Uint8 CREATE_ENTITY_MENU = 0x02;

		}

		class EditorMenu : public Menu
		{
		public:
			explicit EditorMenu(Menu* parent);
			~EditorMenu();

			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			void update(const sf::Event& _event, sf::RenderWindow& _window) override;
			void update(sf::RenderWindow& window) override;

		private:			
			sf::Uint8 state_;

			void create_entity();
			void select_menu();
		};
	}
}
