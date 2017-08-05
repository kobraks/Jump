#pragma once
#include <vector>

struct lua_State;

namespace lua
{
	class LuaScript
	{
	public:
		~LuaScript();
		LuaScript(LuaScript&) = delete;

		static bool load_script(lua_State* lua_state, const std::string& file_name);
		static void lua_gottostack(lua_State* lua_state, const std::string& variable_name);
		static void load_get_keys_function(lua_State* lua_state);
		static std::vector<std::string> get_table_keys(lua_State* lua_state, const std::string& name);
	private:
		LuaScript();
	};
}

