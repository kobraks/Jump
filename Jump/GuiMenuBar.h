#pragma once
#include "GuiItem.h"
#include "GuiTypes.h"
#include "GuiItemCointainer.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiMenuBar : public GuiItem, public GuiItemCointainer
			{
			public:
				explicit GuiMenuBar(GuiItem* parent = nullptr);
				GuiMenuBar(const GuiMenuBar& menu_bar);
				GuiMenuBar(GuiMenuBar&& menu_bar) = default;

				void add(GuiItem* item) override;

				~GuiMenuBar();

				GuiItem* clone() const override;

				GuiMenuBar& operator= (const GuiMenuBar& menu_bar);
				GuiMenuBar& operator= (GuiMenuBar&& menu_bar) = default;
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) override;
			};
		}
	}
}
