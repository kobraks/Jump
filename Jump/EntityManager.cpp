#include "EntityManager.h"

#include <fstream>

#include "Entity.h"
#include "EntityLoader.h"
#include "EntitiesStorageLoader.h"
#include "OutOfRangeException.h"
#include "NotInicializedException.h"
#include "UnableToOpenFileException.h"
#include "BadAllocException.h"
#include "Log.h"

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
	clear();
}

bool jump::entity::EntityManager::empty()
{
	return get_instance()->entities_.empty();
}

jump::entity::Entity* jump::entity::EntityManager::get_entity(size_t index)
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
	clear();

	auto loader = new EntitiesStorageLoader(file_name);
	auto entity_names = loader->get_entities_names();
	delete loader;

	for (auto& entity_name : entity_names)
	{
		try
		{
			get_instance()->load_entity_from_file(entity_name);
		}
		catch (std::exception& exception)
		{
			system::Log::write_error("Unable to load entity", exception.what());
		}
	}
}

void jump::entity::EntityManager::clear()
{
	auto& entities = get_instance()->entities_;

	for (auto& entity : entities)
		delete entity;

	entities.clear();
}

void jump::entity::EntityManager::load_entity_from_file(const std::string& _file_name)
{
	try
	{
		auto entity_loader = new EntityLoader(_file_name);
		entities_.push_back(entity_loader->get_entity());
		delete entity_loader;
	}
	catch (std::bad_alloc& exception)
	{
		system::Log::write_error("Unable to allocate more memory", exception.what());
		throw system::exception::BadAllocException();
	}
	
}

void jump::entity::EntityManager::remove_entity(size_t index)
{
	auto& entities = get_instance()->entities_;

	if (index > 0 && index < entities.size())
	{
		delete entities[index];
		entities.erase(entities.begin() + index);
	}
	else
		throw system::exception::OutOfRangeException();

}

void jump::entity::EntityManager::remove_entity(Entity* entity)
{
	auto& entities = get_instance()->entities_;

	for (size_t i = 0; i < entities.size(); ++i)
		if (entities[i] == entity)
			return remove_entity(i);
}
