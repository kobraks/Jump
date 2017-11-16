#pragma once
#include "GuiItem.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			const flag_t YES_BUTTON = 0x1;
			const flag_t NO_BUTTON = 0x2;
			const flag_t YES_NO_BUTTON = YES_BUTTON | NO_BUTTON;
			const flag_t IGNORE_BUTTON = 0x4;
			const flag_t YES_NO_IGNORE_BUTTON = YES_NO_BUTTON | IGNORE_BUTTON;

			class GuiForm;
			class GuiLabel;

			class GuiMessageBox : public GuiItem
			{
			public:
				GuiMessageBox(GuiItem* parent, const std::string& name, const std::string& text, const flag_t& flags = YES_NO_IGNORE_BUTTON);
				GuiMessageBox(const GuiMessageBox& message_box);
				GuiMessageBox(GuiMessageBox&& message_box) = default;

				void title(const std::string& title);
				std::string title() const;

				void text(const std::string& text);
				std::string text() const;

				flag_t flags() const;
				void flags(const flag_t& flags);

				bool yes_clicked() const;
				bool no_clicked() const;
				bool ignore_clicked() const;

				~GuiMessageBox() override;

				GuiItem* clone() const override;
				void close() const;
				void show() const;

				GuiMessageBox& operator=(const GuiMessageBox& message_box);
				GuiMessageBox& operator=(GuiMessageBox&& message_box) = default;

			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) override;

			private:
				std::string title_;
				flag_t flags_;
				size_t button_cliked_;

				GuiLabel* label_;
				GuiForm* form_;
			};
		}
	}
}