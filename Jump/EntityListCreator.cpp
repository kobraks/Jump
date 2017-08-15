#include "EntityListCreator.h"
#include "EntityManager.h"
#include "Entity.h"

#include <string.h>

jump::utilities::EntityListCreator::EntityListCreator(): list_(nullptr), count_(0)
{
}


jump::utilities::EntityListCreator::~EntityListCreator()
{
	clear();
}

void jump::utilities::EntityListCreator::update()
{
	if (count_ == entity::EntityManager::get_count())
		return;

	clear();
	list_ = new char*[entity::EntityManager::get_count()];

	for (size_t i = 0; i < entity::EntityManager::get_count(); ++i)
	{
		auto entity_type = entity::EntityManager::get_entity(i)->get_type();

		list_[i] = new char[entity_type.size() + 1];

		strcpy_s(list_[i], entity_type.size() + 1, entity_type.c_str());
	}
	count_ = entity::EntityManager::get_count();
}

char** jump::utilities::EntityListCreator::get_list() const
{
	return list_;
}

size_t jump::utilities::EntityListCreator::get_count() const
{
	return count_;
}

void jump::utilities::EntityListCreator::clear()
{
	for (size_t i = 0; i < count_; ++i)
	{
		delete[] list_[i];
		list_[i] = nullptr;
	}

	delete[] list_;
	list_ = nullptr;
}
