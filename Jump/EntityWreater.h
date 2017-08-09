#pragma once
#include <vector>

namespace
{
	namespace entity
	{
		class Entity;

		class EntityWreater
		{
		public:
			EntityWreater(const std::string& file_name, std::vector<Entity*>& entites);
			~EntityWreater();

		private:
			void write_content_table();
			void write_entity(Entity* entity);
		};
	}
}
