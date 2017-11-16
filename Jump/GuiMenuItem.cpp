#include "GuiMenuItem.h"

#include "imgui.h"

jump::system::gui::GuiMenuItem::GuiMenuItem(GuiItem* parent, const std::string& name, const std::string& shortcut,
	const bool& selected, const bool& enabled, event_function on_click) : GuiItem(parent)
{
	name_ = name;
	on_click_ = on_click;
	selected_ = selected;
	enabled_ = enabled;
	shortcut_ = shortcut;
	select_on_click_ = false;
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

bool jump::system::gui::GuiMenuItem::select_on_click() const
{
	return select_on_click_;
}

void jump::system::gui::GuiMenuItem::select_on_click(const bool& select_on_click)
{
	select_on_click_ = select_on_click;
}

jump::system::gui::GuiItem* jump::system::gui::GuiMenuItem::clone() const
{
	auto result = new GuiMenuItem(parent(), name_, shortcut_, selected_, enabled_, on_click_);
	result->select_on_click_ = select_on_click_;

	return result;
}

jump::system::gui::GuiMenuItem& jump::system::gui::GuiMenuItem::operator=(const GuiMenuItem& menu)
{
	auto clone = dynamic_cast<GuiMenuItem*>(menu.clone());

	move_values(clone);
	selected_ = std::move(clone->selected_);
	shortcut_ = std::move(clone->shortcut_);
	name_ = std::move(clone->name_);
	enabled_ = std::move(clone->enabled_);
	select_on_click_ = std::move(clone->select_on_click_);
	on_click_ = std::move(clone->on_click_);


	delete clone;

	return *this;
}

void jump::system::gui::GuiMenuItem::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	if (ImGui::MenuItem(name_.c_str(), shortcut_.c_str(), selected_, enabled_))
	{
		if (select_on_click_)
		{
			if (selected_)
				selected_ = false;
			else
				selected_ = true;
		}

		if (on_click_) on_click_(const_cast<GuiMenuItem*>(this));
	}
}
