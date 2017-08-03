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
			class GuiButton : public GuiItem
			{
			protected:
				typedef std::function<void(const sf::Event&, GuiItem*)> event_function;

			public:
				GuiButton(GuiItem* _parent = nullptr);
				~GuiButton();
			private:
			};
		}
	}
}
