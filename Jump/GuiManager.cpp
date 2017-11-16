#include "GuiManager.h"

#include "GuiItem.h"
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

bool jump::system::gui::GuiManager::exist(GuiItem* item)
{
	if (!item)
		throw exception::NotInicializedException();

	auto& items = get_instance()->items_;

	auto iterator = std::find(items.begin(), items.end(), item);
	return iterator != items.end();
}

void jump::system::gui::GuiManager::remove()
{
	while (!to_remove_.empty())
	{
		items_.erase(to_remove_.front());
		to_remove_.pop();
	}
}

void jump::system::gui::GuiManager::destroy()
{
	while(!to_delete_.empty())
	{
		delete to_delete_.front();
		to_delete_.pop();
	}
}

class jump::system::gui::GuiManager* jump::system::gui::GuiManager::set_window(sf::RenderWindow& _window)
{
	auto instance = get_instance();

	instance->window_ = &_window;
	return instance;
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::clear()
{
	auto instance = get_instance();
	auto& items = instance->items_;
	items.clear();

	return instance;
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::draw()
{
	auto instance = get_instance();
	auto& items = instance->items_;
	auto& window = instance->window_;

	for (auto item : items)
	{
		item->on_draw();
		item->draw(*window, sf::RenderStates());
		item->on_end_draw();
	}

	instance->remove();
	instance->destroy();

	return instance;
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::remove(GuiItem* item)
{
	if (!item)
		throw exception::NotInicializedException();

	auto instance = get_instance();
	auto& items = instance->items_;
	auto& to_remove = instance->to_remove_;

	auto iterator = std::find(items.begin(), items.end(), item);

	if (iterator != items.end())
		to_remove.push(iterator);

	return instance;
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::remove_and_destroy(GuiItem* item)
{
	remove(item);
	get_instance()->to_delete_.push(item);

	return get_instance();
}

jump::system::gui::GuiManager* jump::system::gui::GuiManager::add(GuiItem* item)
{
	if (!item)
		throw exception::NotInicializedException();

	auto instance = get_instance();
	if (instance->exist(item))
		return instance;
	
	auto& items = instance->items_;
	items.push_back(item);

	return instance;
}
