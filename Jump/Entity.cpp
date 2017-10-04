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

sf::Vector2f jump::entity::Entity::get_position() const
{
	return position_;
}

void jump::entity::Entity::set_position(const sf::Vector2f& position)
{
	position_ = position;
}

jump::entity::Entity::Entity(): id_(0), lua_entity_handle_(new LuaEntityHandle(this))
{
}

jump::entity::Entity::Entity(const unsigned int& _id) : Entity()
{
	id_ = _id;
}

jump::entity::Entity::Entity(const Entity& entity): id_(entity.id_), type_(entity.type_), position_(entity.position_)
{
	lua_entity_handle_ = new LuaEntityHandle(*entity.lua_entity_handle_);
	lua_entity_handle_->set_entity(this);

	for(auto& component : entity.components_)
		components_[component.first] = component.second->get_copy();
}

jump::entity::Entity::~Entity()
{
	for (auto& component : components_)
		delete component.second;
}

jump::entity::Entity* jump::entity::Entity::get_copy() const
{
	auto entity = new Entity(*this);
	return entity;
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
