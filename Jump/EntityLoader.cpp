#include "EntityLoader.h"

#include "UnableToLoadException.h"

#include "Entity.h"
#include "GraphicComponent.h"
#include "defines.h"

jump::entity::EntityLoader::EntityLoader(const std::string& _file_name)
{
	lua_state_ = luaL_newstate();

	if (luaL_loadfile(lua_state_, _file_name.c_str()) ||
		lua_pcall(lua_state_, 0, 0, 0)) {
		throw system::exception::UnableToLoadException(_file_name);
	}

	if (lua_state_) luaL_openlibs(lua_state_);

	auto entity_table = LuaIntf::LuaRef(lua_state_, _file_name.c_str());
	entity_ = new Entity();
	entity_->set_type(_file_name);
	entity_->get_lua_handler()->register_functions(lua_state_);
	entity_->get_lua_handler()->set_state(lua_state_);
	entity_->get_lua_handler()->load_script(lua_state_, &entity_table);
	populate_entity(entity_, &entity_table);
}

jump::entity::EntityLoader::~EntityLoader()
{
}

jump::entity::Entity* jump::entity::EntityLoader::get_entity() const
{
	return entity_;
}

void jump::entity::EntityLoader::populate_entity(Entity* entity, LuaIntf::LuaRef* entity_table)
{
	if (entity_table->get<LuaIntf::LuaRef>(GRAPHIC_CODE).isValid())
		add_component<component::GraphicComponent>(entity, entity_table->get<LuaIntf::LuaRef>(GRAPHIC_CODE));
}