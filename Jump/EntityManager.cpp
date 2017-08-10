#include "EntityManager.h"

#include <fstream>

#include "Entity.h"
#include "EntityLoader.h"
#include "OutOfRangeException.h"
#include "NotInicializedException.h"
#include "UnableToOpenFileException.h"
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
	clear();
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
	clear();

	std::fstream file(file_name, std::ios::in);
	if (!file.good())
	{
		file.close();
		throw system::exception::UnableToOpenFileException(file_name);
	}

	std::vector<std::string> entity_names;
	
	std::string line;
	while (std::getline(file, line))
		entity_names.push_back(line);

	for (auto& entity_name : entity_names)
		get_instance()->load_entity_from_file(entity_name);

	file.close();
}

void jump::entity::EntityManager::clear()
{
	auto& entities = get_instance()->entities_;

	for (auto& entity : entities)
		delete &entity;

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
	catch (std::bad_alloc)
	{
		throw system::exception::BadAllocException();
	}
	
}
