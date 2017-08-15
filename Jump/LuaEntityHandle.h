#pragma once
#include <string>


#include <lua/lua.hpp>
#include <lua/LuaIntf.h>

namespace jump
{
	namespace entity
	{
		class Entity;

		class LuaEntityHandle
		{
		public:
			explicit LuaEntityHandle(Entity* entity);
			~LuaEntityHandle();

			Entity* get_entity() const;
			void set_entity(Entity* entity);

			lua_State* get_state() const;
			void set_state(lua_State* lua_state);

			void update();
			void collision(LuaEntityHandle* this_entity, LuaEntityHandle* collide_with);

			void register_functions(lua_State* lua_state);
			void load_script(lua_State* lua_state, LuaIntf::LuaRef* entity_table);

			void set_image(std::string file_name);
		private:
			Entity* entity_;
			lua_State* lua_state_;

			LuaIntf::LuaRef* update_function;
		};
	}
}

