#include "ScriptComponent.h"
#include "UnableToLoadException.h"


jump::component::ScriptComponent::ScriptComponent() : Component(nullptr), lua_state_(nullptr)
{
}


jump::component::ScriptComponent::~ScriptComponent()
{
}

jump::component::ScriptComponent::ScriptComponent(luabridge::LuaRef* _lua) : Component(_lua)
{
	if ((*_lua)["script_name"].isNil())
		throw std::exception();
	luabridge::LuaRef& lua = *_lua;
	file_name_ = lua["script_name"].cast<std::string>();

	lua_state_ = luaL_newstate();

	if (luaL_loadfile(lua_state_, file_name_.c_str()) ||
		lua_pcall(lua_state_, 0, 0, 0)) {
		throw system::exception::UnableToLoadException(file_name_);
	}

	if (lua_state_) luaL_openlibs(lua_state_);
}
