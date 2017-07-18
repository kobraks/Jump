#pragma once

#include <sfml/Graphics.hpp>

#include "GuiDrawable.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			namespace state
			{
				enum
				{
					normal = 0,
					hovered = 1,
					clicked = 2
				};
			}

			class GuiItem : public GuiDrawable
			{
			public:
				GuiItem(GuiItem* _parent = nullptr) : parent_(_parent)
				{}

				virtual void update(sf::Event& _e, sf::RenderWindow& _window) = 0;

				virtual ~GuiItem()
				{
					parent_ = nullptr;
				}

				GuiItem* parent()
				{
					return parent_;
				}

			private:
				GuiItem* parent_;
			};
		}
	}
}

