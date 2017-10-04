#include "GuiItem.h"

jump::system::gui::GuiItem::GuiItem(GuiItem* _parent) : parent_(_parent), active_(true), visable_(true)
{
}

jump::system::gui::GuiItem::~GuiItem() 
{
	parent_ = nullptr;
}

jump::system::gui::GuiItem* jump::system::gui::GuiItem::parent() const
{
	return parent_;
}

sf::Vector2f jump::system::gui::GuiItem::get_position() const
{
	return position_;
}

void jump::system::gui::GuiItem::set_position(const sf::Vector2f& _position)
{
	position_ = _position;
}

bool jump::system::gui::GuiItem::is_active() const
{
	return active_;
}

void jump::system::gui::GuiItem::is_active(const bool& _active)
{
	active_ = _active;
}

bool jump::system::gui::GuiItem::is_visable() const
{
	return visable_;
}

void jump::system::gui::GuiItem::is_visable(const bool& _visalbe)
{
	visable_ = _visalbe;
}

void jump::system::gui::GuiItem::set_parent(GuiItem* parent)
{
	parent_ = parent;
}

std::string jump::system::gui::GuiItem::get_name() const
{
	return name_;
}

void jump::system::gui::GuiItem::set_name(const std::string& name)
{
	name_ = name;
}

int jump::system::gui::GuiItem::get_flags() const
{
	return flags_;
}

void jump::system::gui::GuiItem::set_flags(const int& flags)
{
	flags_ = flags;
}

sf::Vector2f jump::system::gui::GuiItem::get_size() const
{
	return size_;
}

void jump::system::gui::GuiItem::set_size(const sf::Vector2f& size)
{
	size_ = size;
}

bool jump::system::gui::GuiItem::border() const
{
	return border_;
}

void jump::system::gui::GuiItem::border(const bool& border)
{
	border_ = border;
}

std::string jump::system::gui::GuiItem::get_label() const
{
	return label_;
}

void jump::system::gui::GuiItem::set_label(const std::string& label)
{
	label_ = label;
}
