#pragma once

namespace luabridge
{
	class LuaRef;
}

namespace jump
{
	namespace component
	{
		class Component
		{
		public:

			Component(luabridge::LuaRef* _lua_ref)
			{
			}

			virtual ~Component()
			{
			}
		};
	}

}
