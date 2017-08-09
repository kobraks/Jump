#include "PhisicComponent.h"



jump::component::PhisicComponent::PhisicComponent(): Component(nullptr)
{
}


jump::component::PhisicComponent::~PhisicComponent()
{
}

jump::component::PhisicComponent::PhisicComponent(luabridge::LuaRef& lua_ref): Component(&lua_ref)
{
}
