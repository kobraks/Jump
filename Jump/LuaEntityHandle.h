#pragma once

namespace jump
{
	namespace entity
	{
		class Entity;

		class LuaEntityHandle
		{
		public:
			LuaEntityHandle(Entity* entity);
			~LuaEntityHandle();

			Entity* get_entity() const;
			void set_entity(Entity* entity);

		private:
			Entity* entity_;
		};
	}
}

