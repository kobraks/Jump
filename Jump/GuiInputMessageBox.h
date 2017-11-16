#pragma once
#include "GuiItem.h"
#include "GuiForm.h"
#include "GuiMessageBox.h"
#include "GuiInputBox.h"
#include "GuiLabel.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiInputMessageBox : public GuiItem
			{
			public:
				GuiInputMessageBox(GuiItem* parent, const std::string& name, const std::string& text, const std::string& default_text = "", const flag_t& flags = YES_BUTTON);
				~GuiInputMessageBox();

				void set_action_on_close(event_function function);

				void name(const std::string& name) const;
				std::string name() const;

				void text(const std::string& text);
				std::string text() const;

				std::string writed_text() const;

				void close();

				int button_clicked();
				GuiItem* clone() const override;
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) override;
			private:
				GuiForm* form_;
				GuiInputBox* input_;
				GuiLabel* label_;

				int button_clicked_;
				flag_t flags_;
				bool first_draw_;

				event_function on_close_;
			};
		}
	}
}