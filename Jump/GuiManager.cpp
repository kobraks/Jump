#include "GuiManager.h"

#include <algorithm>


jump::system::gui::GuiManager::GuiManager()
{
	window_ = nullptr;
}


jump::system::gui::GuiManager::~GuiManager()
{
	clear();
}

class jump::system::gui::GuiManager* jump::system::gui::GuiManager::set_window(sf::RenderWindow& _window)
{
	get_instance()->window_ = &_window;
	return get_instance();
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::get_instance()
{
	static GuiManager instance;

	return &instance;
}

class jump::system::gui::GuiManager* jump::system::gui::GuiManager::add_item(GuiItem* _item)
{
	if (_item)
	{
		auto iterator = std::find(items_.begin(), items_.end(), _item);
		if (iterator == items_.end())
			items_.push_back(_item);

		return add_item(_item->parent());
	}
	
	return this;

}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::add(GuiItem* _item)
{
	if (_item)
	{
		get_instance()->add_item(_item);
	}
	else
		throw std::exception();

	return get_instance();
}

class jump::system::gui::GuiManager* jump::system::gui::GuiManager::add(GuiItem* _begin, GuiItem* _end)
{
	if (!_begin || !_end)
		throw std::exception();

	for (auto curr = _begin; curr != _end; ++curr)
		get_instance()->add(curr);

	return get_instance();
}


jump::system::gui::GuiManager* jump::system::gui::GuiManager::add(std::initializer_list<GuiItem*> _items)
{
	for (auto item : _items)
		get_instance()->add(item);

	return get_instance();
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::clear()
{
	for (auto item : get_instance()->items_)
		delete item;

	get_instance()->items_.clear();

	return get_instance();
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::draw()
{
	for (auto item : get_instance()->items_)
		
		get_instance()->window_->draw(const_cast<const sf::Drawable&>(*dynamic_cast<sf::Drawable*>(item)));

	return get_instance();
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::update()
{
	for (auto item : get_instance()->items_)
	{
		for (auto event : get_instance()->events_)
			item->update(event, *get_instance()->window_);
	}

	return get_instance();
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::process_events(sf::Event& _event)
{
	get_instance()->events_.push_back(_event);

	return get_instance();
}


