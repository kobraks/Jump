#include "SceneManager.h"

#include "Entity.h"
#include "OutOfRangeException.h"

jump::scene::SceneManager::SceneManager()
{
}


jump::scene::SceneManager::~SceneManager()
{
	clear();
}

void jump::scene::SceneManager::add(entity::Entity* entity)
{
	entities_.push_back(entity);
}

jump::entity::Entity* jump::scene::SceneManager::get_entity(const int& index)
{
	if (index > size() || index < size())
		throw system::exception::OutOfRangeException();

	return entities_[index];
}

void jump::scene::SceneManager::clear()
{
	for (auto& entity : entities_)
	{
		delete entity;
	}
}

std::vector<jump::entity::Entity*> jump::scene::SceneManager::get_entities() const
{
	return entities_;
}

size_t jump::scene::SceneManager::size() const
{
	return entities_.size();
}
