#include "EntityManager.h"

#include "Entity.h"
#include "EntityLoader.h"
#include "OutOfRangeException.h"
#include "NotInicializedException.h"
#include "BadAllocException.h"

jump::entity::EntityManager::EntityManager()
{
}

jump::entity::EntityManager* jump::entity::EntityManager::get_instance()
{
	static EntityManager instance;
	return &instance;
}


jump::entity::EntityManager::~EntityManager()
{
	for (auto& entity : entities_)
		delete entity;
}

jump::entity::Entity* jump::entity::EntityManager::get_entity(unsigned int& index)
{
	auto& entities = get_instance()->entities_;

	if (index >= 0 && index < entities.size())
		return entities[index];
	else
		throw system::exception::OutOfRangeException();
}

void jump::entity::EntityManager::add_entity(Entity* entity)
{
	if (entity)
	{
		get_instance()->entities_.push_back(entity);
	}
	else
		throw system::exception::NotInicializedException();
}

std::vector<jump::entity::Entity*>::size_type jump::entity::EntityManager::get_count()
{
	return get_instance()->entities_.size();
}

void jump::entity::EntityManager::load_from_file(const std::string& file_name)
{
	try
	{
		auto entity_loader = new EntityLoader(file_name);
		get_instance()->entities_ = entity_loader->get_entites();
		delete entity_loader;
	}
	catch(std::bad_alloc)
	{
		throw system::exception::BadAllocException();
	}
}


