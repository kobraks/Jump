#pragma once
#include <vector>
#include "GuiItem.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiItemCointainer
			{
			public:
				GuiItemCointainer();
				GuiItemCointainer(const GuiItemCointainer& item_cointainer);
				GuiItemCointainer(GuiItemCointainer&& item_cointainer) = default;

				virtual ~GuiItemCointainer();
				
				virtual void add(GuiItem* item);
				virtual void insert(size_t index, GuiItem* item);
				virtual void remove(GuiItem* item);
				virtual void remove_and_delete(GuiItem* item);

				std::vector<GuiItem*> get_items() const;
				size_t size() const;

				GuiItemCointainer& operator=(const GuiItemCointainer& item_cointainer);
				GuiItemCointainer& operator=(GuiItemCointainer&& item_cointainer) = default;

			protected:
				/**
				 * \brief checks if item is already defined on the list
				 * \param item this is an item to find
				 * \param result this is a iterator where this item was found 
				 * \return item is on the list or not
				 */
				bool exist(GuiItem* item, std::vector<GuiItem*>::iterator* result = nullptr);
				void clear();
				std::vector<GuiItem*> get_copy() const;
				void move_items(std::vector<GuiItem*>&& items);

				void remove_all_items();

				void draw_items(sf::RenderTarget& target, sf::RenderStates states);
			private:
				std::vector<GuiItem*> items_;
			};
		}
	}
}

