#pragma once

#include <sfml/Graphics.hpp>

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
					NORMAL = 0,
					HOVERED = 1,
					CLICKED = 2
				};
			}

			class GuiItem : public sf::Drawable
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

