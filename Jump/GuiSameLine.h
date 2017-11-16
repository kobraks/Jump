#pragma once

#include "GuiTypes.h"
#include "GuiItem.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiSameLine : public GuiItem
			{
			public:
				GuiSameLine();
				GuiSameLine(GuiItem* parent);
				GuiSameLine(GuiSameLine& item);
				GuiSameLine(GuiSameLine&& item) = default;

				~GuiSameLine() override;

				GuiSameLine& operator= (const GuiSameLine& item);
				GuiSameLine& operator= (GuiSameLine&& item) = default;

				GuiItem* clone() const override;
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) override;
			};
		}
	}
}
