#pragma once

namespace luabridge
{
	class luaRef;
}

namespace jump
{
	namespace component
	{
		class Component
		{
		public:

			Component(luabridge::luaRef* _lua_ref)
			{
			}

			virtual ~Component()
			{
			}
		};
	}

}
