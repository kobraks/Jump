#pragma once

#include <vector>

namespace jump
{
	class Entity;

	class EntityManager
	{
	public:
		~EntityManager();

		static Entity* get_entity(unsigned int& index);
		static void add_entity(Entity* entity);
		
		static std::vector<Entity* >::size_type get_count();
	private:
		EntityManager();
		EntityManager(EntityManager&) = delete;
		std::vector<Entity*> entities_;

		static EntityManager* get_instance();

	};
}
