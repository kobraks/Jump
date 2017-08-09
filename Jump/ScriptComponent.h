#pragma once
#include "Component.h"

#include <string>

#include "lua/lua.hpp"
#include "lua/LuaBridge.h"
namespace jump
{
	namespace component
	{
		class ScriptComponent : public Component
		{
		public:
			ScriptComponent();
			explicit ScriptComponent(luabridge::LuaRef* _lua);

			~ScriptComponent();

		private:
			lua_State* lua_state_;
			std::string file_name_;
		};
	}
}


