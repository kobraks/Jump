#include "GraphicComponent.h"
#include <SFML/Graphics/Sprite.hpp>


jump::component::GraphicComponent::GraphicComponent(luabridge::luaRef* _lua_ref): Component(_lua_ref)
{
}


jump::component::GraphicComponent::~GraphicComponent()
{
}

void jump::component::GraphicComponent::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
}
