#pragma once
#include "Component.h"

namespace jump
{
	namespace system
	{
		class Animation;
	}

	namespace component
	{
		class AnimationComponent : public Component
		{
		public:
			AnimationComponent();
			AnimationComponent(luabridge::LuaRef& lua_ref);

			~AnimationComponent();

		private:
			system::Animation* animation_;
		};


	}
}
