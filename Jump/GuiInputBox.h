#pragma once

#include "GuiItem.h"
#include "GuiTypes.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiInputBox : public GuiItem
			{
			public:
				GuiInputBox();
				explicit GuiInputBox(GuiItem* parent);
				GuiInputBox(GuiItem* parent, const std::string& text);
				GuiInputBox(GuiItem* parent, const std::string& text, const sf::Vector2f& position);
				GuiInputBox(GuiItem* parent, const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size);
				GuiInputBox(GuiItem* parent, const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size, const flag_t& flags);
				GuiInputBox(const GuiInputBox& input);
				GuiInputBox(GuiInputBox&& input) noexcept;

				~GuiInputBox() override;

				GuiItem* clone() const override;

				GuiInputBox& operator= (const GuiInputBox& input);
				GuiInputBox& operator=(GuiInputBox&& input) noexcept;
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
				std::string text_;
				char* buffer_;
				size_t size_;

				void extend_buffer(const size_t& size);
			};
		}
	}
}

