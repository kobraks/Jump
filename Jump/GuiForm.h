#pragma once
#include <list>
#include "GuiTypes.h"
#include "GuiControl.h"
#include "GuiItem.h"
#include "GuiItemCointainer.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			const flag_t GUI_NO_SAVE = 0x1;
			const flag_t GUI_AUTO_RESIZE = 0x2;

			class GuiForm : public GuiControl, public GuiItemCointainer
			{
			public:
				GuiForm();
				explicit GuiForm(GuiItem* parent);
				GuiForm(GuiItem* parent, const std::string& name);
				GuiForm(GuiItem* parent, const std::string& name, const sf::Vector2f& position);
				GuiForm(GuiItem* parent, const std::string& name, const sf::Vector2f& position, const sf::Vector2f& size);
				GuiForm(GuiItem* parent, const std::string& name, const sf::Vector2f& position, const sf::Vector2f& size, const flag_t& flags);
				GuiForm(GuiForm& gui_form);
				GuiForm(GuiForm&& gui_form) = default;
				~GuiForm() override;

				bool is_open() const;
				void close();

				void set_parent(GuiItem* parent) override;

				void set_size(const sf::Vector2f& size);
				sf::Vector2f get_size() const;

				void set_flags(const flag_t& flags);
				flag_t get_flags() const;

				GuiItem* clone() const override;

				GuiForm& operator= (const GuiForm& gui_form);
				GuiForm& operator= (GuiForm&& gui_form) = default;
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			private:
				bool main_form_, open_;
				sf::Vector2f size_;
				flag_t flags_;

				int translate_flags(const flag_t& flags) const;
			};
		}
	}
}
