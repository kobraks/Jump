#include "AnimationComponent.h"

#include "Animation.h"
#include "lua/lua.hpp"
#include "lua/LuaBridge.h"

jump::component::AnimationComponent::AnimationComponent(): Component(nullptr), animation_(nullptr)
{
}


jump::component::AnimationComponent::~AnimationComponent()
{
}

jump::component::AnimationComponent::AnimationComponent(luabridge::LuaRef& lua_ref): Component(&lua_ref), animation_(nullptr)
{
}
