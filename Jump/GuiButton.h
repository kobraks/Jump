#pragma once
#include <string>

#include "GuiTypes.h"
#include "GuiItem.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			
			class GuiButton : public GuiItem
			{
			public:
				GuiButton();
				explicit GuiButton(GuiItem* parent);
				GuiButton(GuiItem* parent, const std::string& name);
				GuiButton(GuiItem* parent, const std::string& name, const sf::Vector2f& position);
				GuiButton(GuiItem* parent, const std::string& name, const sf::Vector2f& position, const sf::Vector2f& size);
				GuiButton(GuiItem* parent, const std::string& name, const sf::Vector2f& position, const sf::Vector2f& size, const flag_t& flags);
				GuiButton(GuiItem* parent, const std::string& name, const sf::Vector2f& position, const sf::Vector2f& size, const flag_t& flags, event_function on_click);
				GuiButton(GuiButton& item);
				GuiButton(GuiButton&& item) = default;

				~GuiButton();

				void set_on_click_action(event_function on_click);
				GuiItem* clone() const override;

				GuiButton& operator= (GuiButton& item);
				GuiButton& operator= (GuiButton&& item) = default;
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			private:
				event_function on_click_;

			};
		}
	}
}
