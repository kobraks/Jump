#include "GuiItem.h"

jump::system::gui::GuiItem::GuiItem(): flag_(0), parent_(nullptr)
{
}

jump::system::gui::GuiItem::GuiItem(GuiItem* parent): flag_(0), parent_(parent)
{
}

jump::system::gui::GuiItem::GuiItem(GuiItem* parent, const std::string& name) : GuiItem(parent)
{
	name_ = name;
}

jump::system::gui::GuiItem::GuiItem(GuiItem* parent, const std::string& name, const sf::Vector2f& position) : GuiItem(parent, name)
{
	position_ = position;
}

jump::system::gui::GuiItem::GuiItem(GuiItem* parent, const std::string& name, const sf::Vector2f& position,
	const sf::Vector2f& size) : GuiItem(parent, name, position)
{
	size_ = size;
}

jump::system::gui::GuiItem::GuiItem(GuiItem* parent, const std::string& name, const sf::Vector2f& position,
	const sf::Vector2f& size, const flag_t& flags) : GuiItem(parent, name, position, size)
{
	flag_ = flags;
}


jump::system::gui::GuiItem::~GuiItem()
{
	parent_ = nullptr;
}

jump::system::gui::GuiItem* jump::system::gui::GuiItem::parent() const
{
	return parent_;
}

void jump::system::gui::GuiItem::set_parent(GuiItem* parent)
{
	parent_ = parent;
}

sf::Vector2f jump::system::gui::GuiItem::get_position() const
{
	return position_;
}

sf::Vector2f jump::system::gui::GuiItem::get_size() const
{
	return size_;
}

std::string jump::system::gui::GuiItem::get_name() const
{
	return name_;
}

jump::system::gui::flag_t jump::system::gui::GuiItem::get_flags() const
{
	return flag_;
}

void jump::system::gui::GuiItem::set_flags(const flag_t& flags)
{
	flag_ = flags;
}

void jump::system::gui::GuiItem::set_name(const std::string& name)
{
	name_ = name;
}

void jump::system::gui::GuiItem::set_position(const sf::Vector2f& position)
{
	position_ = position;
}

void jump::system::gui::GuiItem::set_size(const sf::Vector2f& size)
{
	size_ = size;
}
