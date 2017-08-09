#include "GraphicComponent.h"
#include "lua/lua.hpp"
#include "lua/LuaBridge.h"

jump::component::GraphicComponent::GraphicComponent(luabridge::LuaRef& _lua_ref): Component(&_lua_ref), sprite_(nullptr), texture_(nullptr)
{
}

jump::component::GraphicComponent::GraphicComponent(): Component(nullptr), sprite_(nullptr), texture_(nullptr)
{
}

jump::component::GraphicComponent::~GraphicComponent()
{
}

void jump::component::GraphicComponent::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	if (sprite_)
		_target.draw(*sprite_, _states);
}
