#pragma once
#include <list>
#include "GuiItem.h"
#include "GuiTypes.h"
#include "GuiItemCointainer.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiMenu : public GuiItem, public GuiItemCointainer
			{
			public:
				GuiMenu(GuiItem* parent = nullptr, const std::string& name = "", const bool& enabled = true, event_function on_click = nullptr);
				~GuiMenu();

				void set_action_on_click(event_function on_click);

				void add(GuiItem* item) override;

				std::string name() const;
				void name(const std::string& name);

				bool enabled() const;
				void enabled(const bool& enabled);

				//void set_parent(GuiItem* parent) override;
				GuiItem* clone() const override;
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) override;

			private:
				event_function on_click_;
				bool enabled_;
				std::string name_;
			};
		}
	}
}

