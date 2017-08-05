#include "Engine.h"
#include "GraphicComponent.h"

jump::Engine::Engine(Menu* _parent) : Menu(_parent)
{
}

jump::Engine::~Engine()
{

}

void jump::Engine::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	for (auto entity : entities_)
		_target.draw(const_cast<sf::Drawable&>(*dynamic_cast<sf::Drawable*>(entity->get_component<component::GraphicComponent>())), _states);
}

void jump::Engine::update(const sf::Event& _event, sf::RenderWindow& _window)
{
}
