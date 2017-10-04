#pragma once
#include <string>


#include <lua/lua.hpp>
#include <lua/LuaIntf.h>
#include <SFML/System/Vector2.hpp>

namespace jump
{
	namespace entity
	{
		class Entity;

		class LuaEntityHandle
		{
		public:
			explicit LuaEntityHandle(Entity* entity);
			~LuaEntityHandle();

			Entity* get_entity() const;
			void set_entity(Entity* entity);

			lua_State* get_state() const;
			void set_state(lua_State* lua_state);

			void update();
			void collision(LuaEntityHandle* this_entity, LuaEntityHandle* collide_with);

			void register_functions(lua_State* lua_state);
			void load_script(lua_State* lua_state, LuaIntf::LuaRef* entity_table);

			void set_image(const std::string& file_name);
			void set_position(const float& x, const float& y);
			void set_animation_key(const std::string& animation_key);
			void set_animation_frame(const float& x, const float& y, const float& width, const float& height);
			unsigned int get_current_frame() const;
			std::string get_current_animation_key() const;

			float get_position_x() const;
			float get_position_y() const;
			sf::Vector2f get_position() const;
		private:
			Entity* entity_;
			std::shared_ptr<lua_State> lua_state_;

			std::shared_ptr<LuaIntf::LuaRef> update_;
			std::shared_ptr<LuaIntf::LuaRef> collision_;
		};
	}
}

