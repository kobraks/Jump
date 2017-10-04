#pragma once
#include "GuiItem.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiLabel : public GuiItem
			{
			public:
				explicit GuiLabel(GuiItem* _parent, const std::string& name, const std::string& text);
				~GuiLabel();


			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
				
			};
		}
	}
}

