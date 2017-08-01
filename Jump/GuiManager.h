#pragma once
#include <list>
#include <queue>
#include <initializer_list>
#include <sfml/Graphics.hpp>

#include "GuiItem.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiManager
			{
			public:
				GuiManager(GuiManager&) = delete;
				~GuiManager();

				static GuiManager* set_window(sf::RenderWindow& _window);
				static GuiManager* add(std::initializer_list<GuiItem*> _items);
				static GuiManager* add(GuiItem* _item);
				static GuiManager* add(GuiItem* _begin, GuiItem* _end);

				template<class iterator>
				static GuiManager* add(iterator _begin, iterator _end)
				{
					for (auto curr = _begin; curr != _end; ++curr)
						get_instance()->add(*curr);

					return get_instance();
				}


				static GuiManager* clear();

				static GuiManager* draw();
				static GuiManager* process_events(sf::Event& _event);
				static GuiManager* update();
			private:
				GuiManager();

				std::list<GuiItem*> items_;
				std::list<sf::Event> events_;
				sf::RenderWindow* window_;

				static GuiManager* get_instance();
				GuiManager* add_item(GuiItem* _item);
			};
		}
	}
}
