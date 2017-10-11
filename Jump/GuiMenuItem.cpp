#include "GuiMenuItem.h"

#include "imgui.h"

jump::system::gui::GuiMenuItem::GuiMenuItem(GuiItem* parent, const std::string& name, const std::string& shortcut,
	const bool& selected, const bool& enabled, event_function on_click) : GuiItem(parent)
{
	name_ = name;
	on_click_ = on_click;
	selected_ = selected;
	enabled_ = enabled;
}

jump::system::gui::GuiMenuItem::GuiMenuItem(GuiItem* parent, const std::string& name, const std::string& shortcut,
	event_function on_click) : GuiMenuItem(parent, name, shortcut, false, true, on_click)
{
}

jump::system::gui::GuiMenuItem::GuiMenuItem(const GuiMenuItem& menu)
{
	*this = menu;
}

jump::system::gui::GuiMenuItem::GuiMenuItem(GuiMenuItem&& menu) noexcept
{
	*this = std::move(menu);
}

jump::system::gui::GuiMenuItem::~GuiMenuItem()
{
	on_click_ = nullptr;
}

std::string jump::system::gui::GuiMenuItem::name() const
{
	return name_;
}

void jump::system::gui::GuiMenuItem::name(const std::string& name)
{
	name_ = name;
}

void jump::system::gui::GuiMenuItem::set_on_click_action(event_function on_click)
{
	on_click_ = on_click;
}

std::string jump::system::gui::GuiMenuItem::get_shortcut() const
{
	return shortcut_;
}

void jump::system::gui::GuiMenuItem::set_shortcut(const std::string& shortcut)
{
	shortcut_ = shortcut;
}

bool jump::system::gui::GuiMenuItem::enabled() const
{
	return enabled_;
}

void jump::system::gui::GuiMenuItem::enabled(const bool& enabled)
{
	enabled_ = enabled;
}

bool jump::system::gui::GuiMenuItem::selected() const
{
	return selected_;
}

void jump::system::gui::GuiMenuItem::selected(const bool& selected)
{
	selected_ = selected;
}

jump::system::gui::GuiItem* jump::system::gui::GuiMenuItem::clone() const
{
	return new GuiMenuItem(parent(), name_, shortcut_, selected_, enabled_, on_click_);
}

jump::system::gui::GuiMenuItem& jump::system::gui::GuiMenuItem::operator=(const GuiMenuItem& menu)
{
	auto clone = dynamic_cast<GuiMenuItem*>(menu.clone());
	*this = std::move(*clone);

	delete clone;

	return *this;
}

void jump::system::gui::GuiMenuItem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (ImGui::MenuItem(name_.c_str(), shortcut_.c_str(), selected_, enabled_))
		if (on_click_) on_click_(const_cast<GuiMenuItem*>(this));
}
