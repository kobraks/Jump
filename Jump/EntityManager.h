#pragma once
#include <string>
#include <vector>

namespace jump
{
	namespace entity
	{
		class Entity;

		class EntityManager
		{
		public:
			~EntityManager();

			static Entity* get_entity(unsigned int& index);
			static void add_entity(Entity* entity);

			static std::vector<Entity* >::size_type get_count();
			static void load_from_file(const std::string& file_name);

			static void clear();
		private:
			EntityManager();
			EntityManager(EntityManager&) = delete;
			std::vector<Entity*> entities_;

			void load_entity_from_file(const std::string& _file_name);

			static EntityManager* get_instance();
		};
	}
}
