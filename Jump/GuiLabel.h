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
				GuiLabel();
				explicit GuiLabel(GuiItem* parent);
				GuiLabel(GuiItem* parent, const std::string& text);
				GuiLabel(const GuiLabel& label);
				GuiLabel(GuiLabel&& label) = default;

				void text(const std::string& text);
				std::string text() const;

				~GuiLabel() override;

				GuiItem* clone() const override;

				GuiLabel& operator=(const GuiLabel& label);
				GuiLabel& operator=(GuiLabel&& label) = default;
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) override;

			private:
				std::string text_;
			};
		}
	}
}

