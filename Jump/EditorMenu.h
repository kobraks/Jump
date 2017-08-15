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
			class Menus
			{
			public:
				explicit Menus();
				~Menus();

				void draw();
				bool is_open() const;
				void close();

			private:
				void select_menu(bool* p_open = nullptr);
				void edit_entity(bool* p_open = nullptr);
				static bool is_duplicate(char *str);
				void select_type_of_entity(bool* p_open = nullptr);

				bool show_select_menu_, show_edit_entity_menu_, show_select_type_entity_menu_;
				bool is_open_;

				char* buff_;
				size_t buff_size_;
				size_t selected_;

				entity::Entity* entity_;

				utilities::EntityListCreator* entity_list_creator_;
			}* editor_menu;
		};
	}
}

