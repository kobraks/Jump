#pragma once
#include <list>

#include "GuiItem.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiForm : public GuiItem
			{
			public:
				explicit GuiForm(GuiItem* parent);
				~GuiForm();

				void add_item(GuiItem* item);
				void remove_item(GuiItem* item);


			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
				void set_parent(GuiItem* parent) override;

			private:
				std::list<GuiItem*> items_;
				bool sub_form_;
			};
		}
	}
}