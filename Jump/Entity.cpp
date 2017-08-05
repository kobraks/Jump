#include "Entity.h"
#include "Component.h"

void jump::Entity::add_component(std::type_index _type_index, component::Component* _component)
{
	components_[_type_index] = _component;
}

jump::Entity::Entity()
{
}

jump::Entity::~Entity()
{
	for (auto& component : components_)
		delete component.second;
}
