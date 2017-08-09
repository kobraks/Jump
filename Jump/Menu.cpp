#include "Menu.h"

jump::Menu::Menu(Menu* parent): run_(true), parent_(parent)
{
}

jump::Menu::~Menu()
{
}

jump::Menu* jump::Menu::perent() const
{
	return parent_;
}

bool jump::Menu::is_running() const
{
	return run_;
}

void jump::Menu::stop()
{
	run_ = false;
}

void jump::Menu::register_event(const sf::Event& event)
{
	Events::register_event(event);
}

void jump::Menu::clear_events()
{
	Events::clear_event();
}

std::queue<sf::Event>& jump::Menu::get_events()
{
	return Events::get_events();
}

jump::Menu::Events::Events()
{
}

jump::Menu::Events* jump::Menu::Events::get_instance()
{
	static Events instance;
	return &instance;
}

void jump::Menu::Events::register_event(const sf::Event& event)
{
	get_instance()->events_.push(event);
}

void jump::Menu::Events::clear_event()
{
	auto& events = get_instance()->events_;

	while (!events.empty())
		events.pop();
}

std::queue<sf::Event>& jump::Menu::Events::get_events()
{
	return get_instance()->events_;
}