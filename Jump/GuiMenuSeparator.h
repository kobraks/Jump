#pragma once
#include "GuiItem.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiMenuSeparator : public GuiItem
			{
			public:
				GuiMenuSeparator(GuiItem* parent = nullptr);
				~GuiMenuSeparator();

				GuiItem* clone() const override;
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			};
		}
	}
}