#include "LuaEntityHandle.h"
#include "Entity.h"

jump::entity::LuaEntityHandle::LuaEntityHandle(Entity* entity) : entity_(entity)
{
}


jump::entity::LuaEntityHandle::~LuaEntityHandle()
{
	entity_ = nullptr;
}

jump::entity::Entity* jump::entity::LuaEntityHandle::get_entity() const
{
	return entity_;
}

void jump::entity::LuaEntityHandle::set_entity(Entity* entity)
{
	entity_ = entity;
}
