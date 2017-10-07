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
				GuiItem(GuiItem* parent, const std::string& name);
				GuiItem(GuiItem* parent, const std::string& name, const sf::Vector2f& position);
				GuiItem(GuiItem* parent, const std::string& name, const sf::Vector2f& position, const sf::Vector2f& size);
				GuiItem(GuiItem* parent, const std::string& name, const sf::Vector2f& position, const sf::Vector2f& size, const flag_t& flags);
				GuiItem(GuiItem&) = default;
				GuiItem(GuiItem&&) = default;

				virtual ~GuiItem();

				GuiItem* parent() const;
				virtual void set_parent(GuiItem* parent);

				sf::Vector2f get_position() const;
				sf::Vector2f get_size() const;
				std::string get_name() const;
				flag_t get_flags() const;
				
				void set_flags(const flag_t& flags);
				void set_name(const std::string& name);
				void set_position(const sf::Vector2f& position);
				void set_size(const sf::Vector2f& size);

				virtual GuiItem* clone() const = 0;

			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

			private:
				std::string name_;
				sf::Vector2f size_, position_;
				flag_t flag_;
				GuiItem* parent_;

				friend GuiManager;
			};
		}
	}
}

