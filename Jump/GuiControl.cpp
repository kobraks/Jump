#include "GuiControl.h"

jump::system::gui::GuiControl::GuiControl(GuiItem* parent, const std::string& name, const sf::Vector2f& position) : GuiItem(parent)
{
	name_ = name;
	position_ = position;
}

jump::system::gui::GuiControl::~GuiControl()
{
}

std::string jump::system::gui::GuiControl::name() const
{
	return name_;
}

void jump::system::gui::GuiControl::name(const std::string& name)
{
	name_ = name;
}

sf::Vector2f jump::system::gui::GuiControl::position() const
{
	return position_;
}

void jump::system::gui::GuiControl::position(const sf::Vector2f& position)
{
	position_ = position;
}
