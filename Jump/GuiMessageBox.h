#pragma once
#include "GuiItem.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			const int YES_BUTTON = 0x1;
			const int NO_BUTTON = 0x2;
			const int IGNORE_BUTTON = 0x4;
			const int YES_NO_BUTTON = YES_BUTTON | NO_BUTTON;
			const int YES_NO_IGNORE_BUTTON = YES_NO_BUTTON | IGNORE_BUTTON;

			class GuiForm;

			class GuiMessageBox : public GuiItem
			{
			public:
				explicit GuiMessageBox(GuiItem* _parent, const std::string& name, const std::string& message, const size_t& type);
				~GuiMessageBox();
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			private:
				GuiForm* form;
				size_t type_;
			};
		}
	}
}