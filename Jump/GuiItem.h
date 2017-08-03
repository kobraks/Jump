#pragma once

#include <SFML/Graphics.hpp>

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
				GuiItem(GuiItem* _parent) : parent_(_parent), active_(true), visable_(true)
				{
				}

				virtual void update(const sf::Event& _event, sf::RenderWindow& _window) = 0;

				virtual ~GuiItem()
				{
					parent_ = nullptr;
				}

				GuiItem* parent()
				{
					return parent_;
				}

				sf::Vector2f get_position() const
				{
					return position_;
				}

				virtual void set_position(const sf::Vector2f& _position)
				{
					position_ = _position;
				}

				bool is_active() const
				{
					return active_;
				}

				void is_active(const bool& _active)
				{
					active_ = _active;
				}

				bool is_visable() const
				{
					return visable_;
				}

				void is_visable(const bool& _visalbe)
				{
					visable_ = _visalbe;
				}

			protected:
				sf::Vector2f position_;

			private:
				GuiItem* parent_;
				bool active_;
				bool visable_;

			};
		}
	}
}

