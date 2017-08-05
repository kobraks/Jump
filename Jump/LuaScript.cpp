#include "LuaScript.h"

#include "lua/lua.hpp"

lua::LuaScript::LuaScript()
{
}


lua::LuaScript::~LuaScript()
{
}

bool lua::LuaScript::load_script(lua_State* lua_state, const std::string& file_name)
{
	return true;
}

void lua::LuaScript::lua_gottostack(lua_State* lua_state, const std::string& variable_name)
{
}

void lua::LuaScript::load_get_keys_function(lua_State* lua_state)
{
	std::string code = R"(function getKeys(T)
		s = {}
		for k, v in pairs(t) do
			table.insert(s, k)
		end
		return s
	end)";

	luaL_dostring(lua_state, code.c_str());
}

std::vector<std::string> lua::LuaScript::get_table_keys(lua_State* lua_state, const std::string& name)
{
	lua_getglobal(lua_state, "getKeys");
	if (lua_isnil(lua_state, -1))
	{
		load_get_keys_function(lua_state);
		lua_getglobal(lua_state, "getKeys");
	}

	return std::vector<std::string>();
}
