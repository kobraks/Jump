#include "GuiItemCointainer.h"

#include "NotInicializedException.h"
#include "OutOfRangeException.h"

jump::system::gui::GuiItemCointainer::GuiItemCointainer()
{
}

jump::system::gui::GuiItemCointainer::GuiItemCointainer(const GuiItemCointainer& item_cointainer)
{
	*this = item_cointainer;
}

jump::system::gui::GuiItemCointainer::~GuiItemCointainer()
{
	clear();
}

void jump::system::gui::GuiItemCointainer::add(GuiItem* item)
{
	if (!item)
		throw exception::NotInicializedException();

	if (!exist(item))
		items_.push_back(item);
}

void jump::system::gui::GuiItemCointainer::insert(size_t index, GuiItem* item)
{
	if (!item)
		throw exception::NotInicializedException();

	if (index >= items_.size())
		throw exception::OutOfRangeException();

	auto iterator = items_.begin();
	if (exist(item, &iterator))
	{
		items_.erase(iterator);
		
		items_.insert(items_.begin() + index, item);
	}
		
}

void jump::system::gui::GuiItemCointainer::remove(GuiItem* item)
{
	if (!item)
		throw exception::NotInicializedException();

	auto iterator = items_.begin();
	if (exist(item, &iterator))
		items_.erase(iterator);
}

void jump::system::gui::GuiItemCointainer::remove_and_delete(GuiItem* item)
{
	if (!item)
		throw exception::NotInicializedException();
	auto iterator = items_.begin();
	if (exist(item, &iterator))
	{
		delete *iterator;
		items_.erase(iterator);
	}

}

std::vector<jump::system::gui::GuiItem*> jump::system::gui::GuiItemCointainer::get_items() const
{
	return items_;
}

jump::system::gui::GuiItemCointainer& jump::system::gui::GuiItemCointainer::operator=(
	const GuiItemCointainer& item_cointainer)
{
	for (auto item : item_cointainer.items_)
	{
		items_.push_back(item->clone());
	}
	return *this;
}

bool jump::system::gui::GuiItemCointainer::exist(GuiItem* item, std::vector<jump::system::gui::GuiItem*>::iterator* result)
{
	if (!item)
		throw exception::NotInicializedException();

	for (auto i = items_.begin(); i != items_.end(); ++i)
	{
		if (*i == item)
		{
			if (result)
				*result = i;

			return true;
		}
	}

	return false;
}

void jump::system::gui::GuiItemCointainer::clear()
{
	for (auto item : items_)
	{
		delete item;
	}

	items_.clear();
}

std::vector<jump::system::gui::GuiItem*> jump::system::gui::GuiItemCointainer::get_copy() const
{
	std::vector<GuiItem*> result;

	for (auto item : items_)
		result.push_back(item->clone());

	return result;
}

void jump::system::gui::GuiItemCointainer::move_items(std::vector<jump::system::gui::GuiItem*>&& items)
{
	items_ = std::move(items);
}

void jump::system::gui::GuiItemCointainer::remove_all_items()
{
	items_.clear();
}

size_t jump::system::gui::GuiItemCointainer::size() const
{
	return items_.size();
}
