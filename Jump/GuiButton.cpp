#include "GuiButton.h"

#include "imgui.h"

void jump::system::gui::GuiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (is_visable())
		if (ImGui::Button(get_name().c_str(), get_size()) && is_active())
			if (on_click_)
				on_click_(dynamic_cast<const GuiItem*>(this));
}

jump::system::gui::GuiButton::GuiButton(GuiItem* _parent) : GuiItem(_parent)
{
}

jump::system::gui::GuiButton::GuiButton(const std::string& label, GuiItem* parent): GuiItem(parent)
{
	set_label(label);
}

jump::system::gui::GuiButton::~GuiButton()
{
}

void jump::system::gui::GuiButton::set_on_click_action(event_function on_click)
{
	on_click_ = on_click;
}
