#include "GuiMenu.h"

#include "imgui.h"

#include "NotInicializedException.h"

jump::system::gui::GuiMenu::GuiMenu(GuiItem* parent, const std::string& name, const bool& enabled, event_function on_click) : GuiItem(parent)
{
	name_ = name;
	on_click_ = on_click;
	enabled_ = enabled;
}

jump::system::gui::GuiMenu::~GuiMenu()
{
	on_click_ = nullptr;
}

void jump::system::gui::GuiMenu::add(GuiItem* item)
{
	if (!item)
		throw exception::NotInicializedException();

	if (dynamic_cast<GuiMenu*>(item) || dynamic_cast<GuiItem*>(item))
		GuiItemCointainer::add(item);
	else
		throw std::exception(); //TODO exception
}

std::string jump::system::gui::GuiMenu::name() const
{
	return name_;
}

void jump::system::gui::GuiMenu::name(const std::string& name)
{
	name_ = name;
}

void jump::system::gui::GuiMenu::set_action_on_click(event_function on_click)
{
	on_click_ = on_click;
}

bool jump::system::gui::GuiMenu::enabled() const
{
	return enabled_;
}

void jump::system::gui::GuiMenu::enabled(const bool& enabled)
{
	enabled_ = enabled;
}

jump::system::gui::GuiItem* jump::system::gui::GuiMenu::clone() const
{
	return new GuiMenu(parent(), name_,enabled_, on_click_);
}

void jump::system::gui::GuiMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (ImGui::BeginMenu(name_.c_str(), enabled_))
	{
		if (on_click_)
			on_click_(const_cast<GuiMenu*>(this));

		for (auto item : get_items())
			target.draw(static_cast<sf::Drawable&>(*dynamic_cast<sf::Drawable*>(item)), states);

		ImGui::EndMenu();
	}
}

