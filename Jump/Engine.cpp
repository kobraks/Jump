#include "Engine.h"
#include "GraphicComponent.h"
#include "EntityManager.h"


jump::Engine::Engine(Menu* _parent) : Menu(_parent)
{
}

jump::Engine::~Engine()
{

}

void jump::Engine::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	/*for (unsigned int i = 0; i < entity::EntityManager::get_count(); ++i)
	{
		_target.draw(const_cast<sf::Drawable&>(*dynamic_cast<sf::Drawable*>(entity::EntityManager::get_entity(i)->get_component<component::GraphicComponent>())), _states);
	}*/
}

void jump::Engine::update(sf::RenderWindow& window)
{
}

