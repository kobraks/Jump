#include "LuaEntityHandle.h"
#include "Entity.h"

#include "GraphicComponent.h"
#include "Log.h"

#define ADD_FUNCTION(x) addFunction(#x, &LuaEntityHandle::x)

jump::entity::LuaEntityHandle::LuaEntityHandle(Entity* entity) : entity_(entity), lua_state_(nullptr), update_function(nullptr)
{
}


jump::entity::LuaEntityHandle::~LuaEntityHandle()
{
	entity_ = nullptr;
	lua_close(lua_state_);
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
	return lua_state_;
}

void jump::entity::LuaEntityHandle::set_state(lua_State* lua_state)
{
	lua_state_ = lua_state;
}

void jump::entity::LuaEntityHandle::update()
{
	if (update_function)
	{
		try
		{
			(*update_function)();
		}
		catch (LuaIntf::LuaException& exception)
		{
			system::Log::write_error("Unable to run update function", exception.what());
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
	.endClass();
}

void jump::entity::LuaEntityHandle::load_script(lua_State* lua_state, LuaIntf::LuaRef* entity_table)
{
	if ((update_function = new LuaIntf::LuaRef(entity_table->get<LuaIntf::LuaRef>("update")))->isValid())
	{
		if (!update_function->isFunction())
		{
			system::Log::write_error("Unable to find update function");
			delete update_function;
			update_function = nullptr;
		}
	}
	else
	{
		system::Log::write_error("Unable to find update function");
		delete update_function;
		update_function = nullptr;
	}
}

void jump::entity::LuaEntityHandle::set_image(std::string file_name)
{
	auto gr = entity_->get_component<component::GraphicComponent>();
	if (gr)
	{
		//TODO graphics
	}
	else
		system::Log::write_error("Unable to get graphic component", "Graphic component for selected entity does not exist");
}
