#include "Entity.h"
#include "Component.h"

void jump::entity::Entity::add_component(std::type_index _type_index, jump::component::Component* _component)
{
	auto component = components_.find(_type_index);
	if (component != components_.end())
		delete component->second;

	components_[_type_index] = _component;
}

jump::entity::LuaEntityHandle* jump::entity::Entity::get_lua_handler() const
{
	return lua_entity_handle_;
}

void jump::entity::Entity::set_lua_handler(LuaEntityHandle* lua_entity_handle)
{
	delete lua_entity_handle_;
	lua_entity_handle_ = lua_entity_handle;
}

jump::entity::Entity::Entity(): id_(0), lua_entity_handle_(new LuaEntityHandle(this))
{
}

jump::entity::Entity::Entity(const unsigned int& _id) : Entity()
{
	id_ = _id;
}

jump::entity::Entity::~Entity()
{
	for (auto& component : components_)
		delete component.second;
}

void jump::entity::Entity::set_type(const std::string& type)
{
	type_ = type;
}

std::string jump::entity::Entity::get_type() const
{
	return type_;
}

unsigned jump::entity::Entity::get_id() const
{
	return id_;
}

void jump::entity::Entity::set_id(unsigned int & id)
{
	id_ = id;
}
