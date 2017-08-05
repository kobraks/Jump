#include "EntityManager.h"

#include "Entity.h"
#include "OutOfRangeException.h"
#include "NotInicializedException.h"

jump::EntityManager::EntityManager()
{
}

jump::EntityManager* jump::EntityManager::get_instance()
{
	static EntityManager instance;
	return &instance;
}


jump::EntityManager::~EntityManager()
{
	for (auto& entity : entities_)
		delete entity;
}

jump::Entity* jump::EntityManager::get_entity(unsigned int& index)
{
	auto& entities = get_instance()->entities_;

	if (index >= 0 && index < entities.size())
		return entities[index];
	else
		throw system::exception::OutOfRangeException();
}

void jump::EntityManager::add_entity(Entity* entity)
{
	if (entity)
	{
		get_instance()->entities_.push_back(entity);
	}
	else
		throw system::exception::NotInicializedException();
}

std::vector<jump::Entity*>::size_type jump::EntityManager::get_count()
{
	return get_instance()->entities_.size();
}


