#pragma once

#include <SFML/Graphics/Drawable.hpp>

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiDrawable : public sf::Drawable
			{
				virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const = 0;
			};
		}
	}
}