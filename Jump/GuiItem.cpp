#include "GuiItem.h"

jump::system::gui::GuiItem::GuiItem(): parent_(nullptr)
{
}

jump::system::gui::GuiItem::GuiItem(GuiItem* parent) : parent_(parent)
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

void jump::system::gui::GuiItem::set_parent(GuiItem* parent)
{
	parent_ = parent;
}

void jump::system::gui::GuiItem::set_action_on_draw(std::function<void(GuiItem*)> function)
{
	on_draw_ = function;
}

void jump::system::gui::GuiItem::set_action_on_end_draw(std::function<void(GuiItem*)> function)
{
	on_end_draw_ = function;
}

void jump::system::gui::GuiItem::on_draw() const
{
	if (on_draw_)
		on_draw_(const_cast<GuiItem*>(this));
}

void jump::system::gui::GuiItem::on_end_draw() const
{
	if (on_end_draw_)
		on_end_draw_(const_cast<GuiItem*>(this));
}

void jump::system::gui::GuiItem::copy_values(GuiItem* item)
{
	on_end_draw_ = item->on_end_draw_;
	on_draw_ = item->on_draw_;
	parent_ = item->parent_;
}

void jump::system::gui::GuiItem::move_values(GuiItem* item)
{
	on_end_draw_ = std::move(item->on_end_draw_);
	item->on_end_draw_ = nullptr;

	on_draw_ = std::move(item->on_draw_);
	item->on_draw_ = nullptr;

	parent_ = std::move(item->parent_);
	item->parent_ = nullptr;
}
