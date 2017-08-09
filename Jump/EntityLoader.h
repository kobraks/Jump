#pragma once
#include <string>
#include "lua/lua.hpp"
#include "lua/LuaBridge.h"
#include <vector>

namespace jump
{
	namespace component
	{
		class GraphicComponent;
		class PhisicComponent;
		class AnimationComponent;
	}

	namespace entity
	{
		class Entity;

		class EntityLoader
		{
		public:
			explicit EntityLoader(const std::string& _file_name);
			~EntityLoader();

			std::vector<Entity*>& get_entites();

		private:
			static void populate_entity(Entity* entity, luabridge::LuaRef& table);

			std::vector<Entity*> entities_;
			std::vector<std::string> get_table_kays(const std::string& table_name);
			lua_State* lua_state_;
		};
	}
}
