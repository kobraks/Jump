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
				GuiSameLine(GuiItem* parent, const std::string& name);
				GuiSameLine(GuiItem* parent, const std::string& name, const sf::Vector2f& position);
				GuiSameLine(GuiItem* parent, const std::string& name, const sf::Vector2f& position, const sf::Vector2f& size);
				GuiSameLine(GuiItem* parent, const std::string& name, const sf::Vector2f& position, const sf::Vector2f& size, const flag_t& flags);
				GuiSameLine(GuiSameLine& item);
				GuiSameLine(GuiSameLine&& item) = default;

				~GuiSameLine() override;

				GuiSameLine& operator= (const GuiSameLine& item);
				GuiSameLine& operator= (GuiSameLine&& item) = default;

				GuiItem* clone() const override;
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			};
		}
	}
}
