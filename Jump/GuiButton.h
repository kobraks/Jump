#pragma once
#include <functional>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "GuiItem.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			typedef std::function<void(const GuiItem*)> event_function;
			
			class GuiButton : public GuiItem
			{
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			public:
				explicit GuiButton(GuiItem* _parent = nullptr);
				explicit GuiButton(const std::string& label, GuiItem* parent = nullptr);

				~GuiButton();

				void set_on_click_action(event_function on_click);
			private:
				event_function on_click_;

			};
		}
	}
}
