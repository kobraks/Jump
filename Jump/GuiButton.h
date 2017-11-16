#pragma once
#include <string>

#include "GuiTypes.h"
#include "GuiItem.h"
#include "GuiControl.h"
#include <SFML/System/Vector2.hpp>

namespace jump
{
	namespace system
	{
		namespace gui
		{
			
			class GuiButton : public GuiControl
			{
			public:
				explicit GuiButton(GuiItem* parent = nullptr, const std::string& name = "", const sf::Vector2f& position = sf::Vector2f(-1, -1), const sf::Vector2f& size = sf::Vector2f(0, 0), event_function on_click = nullptr);
				GuiButton(GuiButton& item);
				GuiButton(GuiButton&& item) = default;

				~GuiButton() override;

				void size(const sf::Vector2f& size);
				sf::Vector2f size() const;

				void set_on_click_action(event_function on_click);
				GuiItem* clone() const override;

				GuiButton& operator= (GuiButton& item);
				GuiButton& operator= (GuiButton&& item) = default;
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) override;

			private:
				event_function on_click_;
				sf::Vector2f size_;
			};
		}
	}
}
