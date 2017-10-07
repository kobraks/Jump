#pragma once
#include <list>
#include "GuiTypes.h"
#include "GuiItem.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			const flag_t GUI_NO_SAVE = 0x1;
			const flag_t GUI_AUTO_RESIZE = 0x2;

			class GuiForm : public GuiItem
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

				void set_parent(GuiItem* parent) override;

				void add_item(GuiItem* item);
				void remove(GuiItem* item);
				void remove_and_destroy(GuiItem* item);

				bool exist(GuiItem* item);

				GuiItem* clone() const override;

				GuiForm& operator= (const GuiForm& gui_form);
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			private:
				std::list<GuiItem*> items_;
				bool main_form_, open_;

				int translate_flags(const flag_t& flags) const;
			};
		}
	}
}