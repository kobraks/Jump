#pragma once

#include <SFML/Graphics.hpp>
#include "GuiTypes.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiManager;

			class GuiItem : public sf::Drawable
			{
			public:
				GuiItem();
				explicit GuiItem(GuiItem* parent);
				GuiItem(GuiItem&) = default;
				GuiItem(GuiItem&&) = default;

				virtual ~GuiItem();

				GuiItem* parent() const;
				virtual void set_parent(GuiItem* parent);

				virtual GuiItem* clone() const = 0;

			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
				
			private:
				GuiItem* parent_;

				friend GuiManager;
			};
		}
	}
}

