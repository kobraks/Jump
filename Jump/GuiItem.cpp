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
