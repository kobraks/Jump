#include "Component.h"

jump::component::Component::Component(entity::Entity* entity): entity_(entity)
{
}

jump::component::Component::~Component()
{
}

jump::entity::Entity* jump::component::Component::get_entity() const
{
	return entity_;
}
