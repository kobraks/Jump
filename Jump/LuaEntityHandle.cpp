#include "LuaEntityHandle.h"
#include "Entity.h"

#include "GraphicComponent.h"
#include "Log.h"

#define ADD_FUNCTION(x) addFunction(#x, &LuaEntityHandle::x)

jump::entity::LuaEntityHandle::LuaEntityHandle(Entity* entity) : entity_(entity), lua_state_(nullptr), update_(nullptr)
{
}


jump::entity::LuaEntityHandle::~LuaEntityHandle()
{
	entity_ = nullptr;
}

jump::entity::Entity* jump::entity::LuaEntityHandle::get_entity() const
{
	return entity_;
}

void jump::entity::LuaEntityHandle::set_entity(Entity* entity)
{
	entity_ = entity;
}

lua_State* jump::entity::LuaEntityHandle::get_state() const
{
	return &*lua_state_;
}

void jump::entity::LuaEntityHandle::set_state(lua_State* lua_state)
{
	lua_state_ = std::shared_ptr<lua_State>(lua_state, [](lua_State* lua_state) { lua_close(lua_state); });
}

void jump::entity::LuaEntityHandle::update()
{
	if (update_)
	{
		try
		{
			(*update_)();
		}
		catch (LuaIntf::LuaException& exception)
		{
			system::Log::write_error("\"" + entity_->get_type() +  "\"Unable to run update function", exception.what());
		}
	}
	else
		system::Log::write_error(entity_->get_type() + "update function does not exist");
}

void jump::entity::LuaEntityHandle::collision(LuaEntityHandle* this_entity, LuaEntityHandle* collide_with)
{
}

void jump::entity::LuaEntityHandle::register_functions(lua_State* lua_state)
{
	LuaIntf::LuaBinding(lua_state)
		.beginModule("log")
		.addFunction("write", system::Log::write)
		.addFunction("write_error", system::Log::write_error)
	.endModule();

	LuaIntf::LuaBinding(lua_state)
		.beginClass<LuaEntityHandle>("LuaEntityHandle")
		.ADD_FUNCTION(set_image)
		.ADD_FUNCTION(set_position)
		.ADD_FUNCTION(set_animation_key)
		.ADD_FUNCTION(set_animation_frame)
		.ADD_FUNCTION(get_current_frame)
		.ADD_FUNCTION(get_current_animation_key)
		.ADD_FUNCTION(get_position_x)
		.ADD_FUNCTION(get_position_y)
		.ADD_FUNCTION(get_position)
	.endClass();
}

void jump::entity::LuaEntityHandle::load_script(lua_State* lua_state, LuaIntf::LuaRef* entity_table)
{
	update_ = std::make_shared<LuaIntf::LuaRef>(LuaIntf::LuaRef(entity_table->get<LuaIntf::LuaRef>("update")));

	if (update_->isValid())
	{
		if (!update_->isFunction())
		{
			system::Log::write_error("Unable to find update function");
			update_ = nullptr;
		}
	}
	else
	{
		system::Log::write_error("Unable to find update function");
		update_ = nullptr;
	}
}

void jump::entity::LuaEntityHandle::set_image(const std::string& file_name)
{
	if (auto gr = entity_->get_component<component::GraphicComponent>())
	{
		//TODO
	}
	else
		system::Log::write_error("Graphic component for \"" + entity_->get_type() + "\" entity does not exist");
}

void jump::entity::LuaEntityHandle::set_position(const float& x, const float& y)
{
	entity_->set_position(sf::Vector2f(x, y));
}

void jump::entity::LuaEntityHandle::set_animation_key(const std::string& animation_key)
{
}

void jump::entity::LuaEntityHandle::set_animation_frame(const float& x, const float& y, const float& width, const float& height)
{
}

unsigned jump::entity::LuaEntityHandle::get_current_frame() const
{
	return 0;
}

std::string jump::entity::LuaEntityHandle::get_current_animation_key() const
{
	return "";
}

float jump::entity::LuaEntityHandle::get_position_x() const
{
	return get_position().x;
}

float jump::entity::LuaEntityHandle::get_position_y() const
{
	return get_position().y;
}

sf::Vector2f jump::entity::LuaEntityHandle::get_position() const
{
	return sf::Vector2f(0, 0);
}
