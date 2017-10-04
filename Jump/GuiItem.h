#pragma once

#include <SFML/Graphics.hpp>
#include "imgui.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiItem : public sf::Drawable
			{
			public:
				explicit GuiItem(GuiItem* _parent);
				virtual ~GuiItem();

				GuiItem* parent() const;
				sf::Vector2f get_position() const;
				virtual void set_position(const sf::Vector2f& _position);
				bool is_active() const;
				void is_active(const bool& _active);
				bool is_visable() const;
				void is_visable(const bool& _visalbe);
				virtual void set_parent(GuiItem* parent);

				std::string get_name() const;
				void set_name(const std::string& name);

				int get_flags() const;
				void set_flags(const int& flags);

				sf::Vector2f get_size() const;
				void set_size(const sf::Vector2f& size);

				bool border() const;
				void border(const bool& border);

				std::string get_label() const;
				void set_label(const std::string& label);
			protected:
				sf::Vector2f position_;
				std::string name_;
				std::string label_;

				int flags_;
				bool border_;
				sf::Vector2f size_;

			private:
				GuiItem* parent_;
				bool active_;
				bool visable_;

			};
		}
	}
}

