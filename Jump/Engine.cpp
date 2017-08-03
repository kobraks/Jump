#include "Engine.h"



jump::Engine::Engine(Menu* _parent) : Menu(_parent), map_(nullptr)
{
}

jump::Engine::~Engine()
{

}

void jump::Engine::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(*map_, _states);
}

void jump::Engine::update(const sf::Event& _event, sf::RenderWindow& _window)
{
	map_->update(_event, _window);
}
