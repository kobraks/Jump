#include "Entity.h"
#include "Component.h"

void jump::entity::Entity::add_component(std::type_index _type_index, jump::component::Component* _component)
{
	components_[_type_index] = _component;
}

jump::entity::Entity::Entity(): id_(0)
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

unsigned jump::entity::Entity::get_id() const
{
	return id_;
}
