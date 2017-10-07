#pragma once
#include <list>
#include <sfml/Graphics.hpp>
#include <queue>

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiItem;

			class GuiManager
			{
			public:
				GuiManager(GuiManager&) = delete;
				GuiManager(GuiManager&&) = delete;
				~GuiManager();

				static GuiManager* set_window(sf::RenderWindow& _window);
				static GuiManager* clear();
				static GuiManager* draw();

				static GuiManager* remove(GuiItem* item);
				static GuiManager* remove_and_destroy(GuiItem* item);
				static GuiManager* add(GuiItem* item);

				GuiManager& operator=(GuiManager&) = delete;
				GuiManager& operator=(GuiManager&&) = delete;
			private:
				GuiManager();

				std::list<GuiItem*> items_;
				std::queue<std::list<GuiItem*>::iterator> to_remove_;
				std::queue<GuiItem*> to_delete_;
				sf::RenderWindow* window_;

				static GuiManager* get_instance();
				bool exist(GuiItem* item);

				void remove();
				void destroy();
			};
		}
	}
}
