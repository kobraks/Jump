#pragma once
#include "GuiItem.h"
#include <SFML/System/Vector2.hpp>

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiControl : public GuiItem
			{
			public:
				GuiControl(GuiItem* parent = nullptr, const std::string& name = "", const sf::Vector2f& position = sf::Vector2f(0,0));
				GuiControl(GuiControl& control) = default;
				GuiControl(GuiControl&& control) = default;

				virtual ~GuiControl();

				std::string name() const;
				void name(const std::string& name);

				sf::Vector2f position() const;
				void position(const sf::Vector2f& position);

				GuiControl& operator=(const GuiControl&) = default;
				GuiControl& operator=(GuiControl&&) = default;

			private:
				sf::Vector2f position_;
				std::string name_;
			};
		}
	}
}

