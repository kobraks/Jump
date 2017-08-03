#include "GuiManager.h"

#include "NotInicializedException.h"

jump::system::gui::GuiManager::GuiManager()
{
	window_ = nullptr;
}


jump::system::gui::GuiManager::~GuiManager()
{
	clear();
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::get_instance()
{
	static GuiManager instance;

	return &instance;
}

class jump::system::gui::GuiManager* jump::system::gui::GuiManager::set_window(sf::RenderWindow& _window)
{
	auto instance = get_instance();

	instance->window_ = &_window;
	return instance;
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
	else
		throw exception::NotInicializedException();
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::add(GuiItem* _item)
{
	auto instance = get_instance();

	if (_item)
	{
		instance->add_item(_item);
	}
	else
		throw exception::NotInicializedException();

	return instance;
}

class jump::system::gui::GuiManager* jump::system::gui::GuiManager::add(GuiItem* _begin, GuiItem* _end)
{
	if (!_begin || !_end)
		throw exception::NotInicializedException();

	auto instance = get_instance();

	for (auto curr = _begin; curr != _end; ++curr)
		instance->add(curr);

	return instance;
}


jump::system::gui::GuiManager* jump::system::gui::GuiManager::add(std::initializer_list<GuiItem*> _items)
{
	auto instance = get_instance();

	for (auto item : _items)
		instance->add(item);

	return instance;
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::clear()
{
	auto instance = get_instance();

	for (auto item : instance->items_)
		delete item;

	instance->items_.clear();

	return instance;
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::draw()
{
	auto instance = get_instance();

	for (auto item : instance->items_)
		if (item->is_visable())
			instance->window_->draw(const_cast<const sf::Drawable&>(*dynamic_cast<sf::Drawable*>(item)));

	return instance;
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::update()
{
	auto instance = get_instance();

	for (auto item : instance->items_)
	{
		if (item->is_active())
			for (auto event : instance->events_)
				item->update(event, *instance->window_);
	}

	return instance;
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::register_event(const sf::Event& _event)
{
	auto instance = get_instance();

	instance->events_.push_back(_event);

	return instance;
}


