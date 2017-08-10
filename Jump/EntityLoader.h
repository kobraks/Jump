#pragma once
#include <string>
#include <vector>
#include "Entity.h"

#include "lua/lua.hpp"
#include "lua/LuaIntf.h"

namespace jump
{
	namespace component
	{
		class Component;
	}

	namespace entity
	{
		class EntityLoader
		{
		public:
			explicit EntityLoader(const std::string& _file_name);
			~EntityLoader();

			Entity* get_entity() const;
		private:
			static void populate_entity(Entity* entity, LuaIntf::LuaRef* table);

			template<class T>
			static void add_component(Entity* entity, LuaIntf::LuaRef component_table);

			lua_State* lua_state_;
			Entity* entity_;
		};

		template <class T>
		void EntityLoader::add_component(Entity* entity, LuaIntf::LuaRef component_table)
		{
			if (entity)
				entity->add_component<T>(new T(entity, component_table));
		}
	}
}
