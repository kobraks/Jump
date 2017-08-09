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
			const sf::Uint8 EDIT_ENTITY_MENU = 0x03;
			const sf::Uint8 EDIT_MAP_MENU = 0x04;
			const sf::Uint8 CREATE_MAP_MENU = 0x05;
			const sf::Uint8 BACK = 0x06;
		}

		class EditorMenu : public Menu
		{
		public:
			explicit EditorMenu(Menu* parent);
			~EditorMenu();

			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			void update(sf::RenderWindow& window) override;

		private:			
			sf::Uint8 state_;

			class Menus
			{
			public:
				explicit Menus();
				~Menus();

				sf::Uint8 get_state() const;
				void set_state(sf::Uint8 state);

				void draw();

			private:
				sf::Uint8 state_;

				void create_entity();
				void select_menu();
			}* editor_menu;
		};
	}
}
