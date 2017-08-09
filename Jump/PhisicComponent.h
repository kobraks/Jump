#pragma once
#include "Component.h"

namespace jump
{
	namespace component
	{
		class PhisicComponent : public Component
		{
		public:
			PhisicComponent();
			PhisicComponent(luabridge::LuaRef& lua_ref);
			~PhisicComponent();
		};
	}
}

