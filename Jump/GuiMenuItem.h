#pragma once
#include "GuiItem.h"
#include "GuiTypes.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiMenuItem : public GuiItem
			{
			public:
				GuiMenuItem(GuiItem* parent, const std::string& name, const std::string& shortcut, const bool& selected = false, const bool& enabled = true, event_function on_click = nullptr);
				GuiMenuItem(GuiItem* parent, const std::string& name, const std::string& shortcut, event_function on_click);
				GuiMenuItem(const GuiMenuItem& menu);
				GuiMenuItem(GuiMenuItem&& menu) noexcept;


				~GuiMenuItem() override;

				std::string name() const;
				void name(const std::string& name);

				void set_on_click_action(event_function on_click);

				std::string get_shortcut() const;
				void set_shortcut(const std::string& shortcut);
				
				bool enabled() const;
				void enabled(const bool& enabled);

				bool selected() const;
				void selected(const bool& selected);

				GuiItem* clone() const override;
				
				GuiMenuItem& operator=(const GuiMenuItem& menu);
				GuiMenuItem& operator=(GuiMenuItem&& menu) = default;
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			private:
				event_function on_click_;
				std::string shortcut_, name_;
				bool selected_, enabled_;

			};
		}
	}
}