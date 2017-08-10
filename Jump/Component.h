#pragma once

struct lua_State;

namespace LuaIntf
{
	class LuaRef;
	class LuaState;
}

namespace jump
{
	namespace entity
	{
		class Entity;
	}

	namespace component
	{
		class Component
		{
		public:
			explicit Component(entity::Entity* entity);

			virtual ~Component();

			entity::Entity* get_entity() const;
		private:
			entity::Entity* entity_;
		};
	}

}
