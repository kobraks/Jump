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
			virtual Component* get_copy() const = 0;
		private:
			entity::Entity* entity_;
		};
	}

}
