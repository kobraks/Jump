#include "EntityLoader.h"

#include <iostream>

#include "BadAllocException.h"
#include "UnableToLoadException.h"

#include "Entity.h"
#include "ScriptComponent.h"
#include "GraphicComponent.h"
#include "AnimationComponent.h"
#include "PhisicComponent.h"

jump::entity::EntityLoader::EntityLoader(const std::string& _file_name)
{
	lua_state_ = luaL_newstate();

	if (luaL_loadfile(lua_state_, _file_name.c_str()) ||
		lua_pcall(lua_state_, 0, 0, 0)) {
		throw system::exception::UnableToLoadException(_file_name);
	}

	if (lua_state_) luaL_openlibs(lua_state_);

	auto content_table = luabridge::getGlobal(lua_state_, "content");
	auto content_keys = get_table_kays("content");

	for(auto key : content_keys)
	{
		try
		{
			luabridge::LuaRef table = content_table[key];
			if (!table["ignore"].isNil() && table["ignore"].cast<bool>())
			{
				auto entity = new Entity(entities_.size());
				if (!table.isNil() && table.isTable())
					populate_entity(entity, table);
				entities_.push_back(entity);
			}
		}
		catch (std::bad_alloc)
		{
			throw system::exception::BadAllocException();
		}
	}
}

jump::entity::EntityLoader::~EntityLoader()
{
	lua_close(lua_state_);
	entities_.clear();
}

std::vector<jump::entity::Entity*>& jump::entity::EntityLoader::get_entites()
{
	return entities_;
}

void jump::entity::EntityLoader::populate_entity(Entity* entity, luabridge::LuaRef& table)
{
	if(!table["graphic"].isNil())
	{
		luabridge::LuaRef graphic_settings = table["graphic"];
		entity->add_component<component::GraphicComponent>(new component::GraphicComponent(graphic_settings));
	}

	if (!table["script"].isNil())
	{
		luabridge::LuaRef script_settings = table["script"];
		entity->add_component<component::ScriptComponent>(new component::ScriptComponent(script_settings));
	}

	if (!table["animation"].isNil())
	{
		luabridge::LuaRef animation_settings = table["animation"];
		entity->add_component<component::AnimationComponent>(new component::AnimationComponent(animation_settings));
	}

	if (!table["phisic"].isNil())
	{
		luabridge::LuaRef phisic_settings = table["phisic"];
		entity->add_component<component::PhisicComponent>(new component::PhisicComponent(phisic_settings));
	}
}

std::vector<std::string> jump::entity::EntityLoader::get_table_kays(const std::string& table_name)
{
	std::string code = R"(function getKeys(name) 
		s = "" 
		for	k, v in pairs(_G[name]) do
			s = s..k..","
		end
		return s
	end)";

	luaL_loadstring(lua_state_, code.c_str());
	lua_pcall(lua_state_, 0, 0, 0);
	lua_getglobal(lua_state_, "getKeys");
	lua_pushstring(lua_state_, table_name.c_str());
	lua_pcall(lua_state_, 1, 1, 0);

	std::string test = lua_tostring(lua_state_, -1);
	std::vector<std::string> strings;
	std::string temp = "";
#ifdef _DEBUG
	std::cout << "TEMP: " << test << std::endl;
#endif
	for (unsigned int i = 0; i < test.size(); i++)
	{
		if (test.at(i) != ',')
			temp += test.at(i);
		else
		{
			strings.push_back(temp);
			temp = "";
		}
	}

	auto n = lua_gettop(lua_state_);
	lua_pop(lua_state_, n);

	return strings;
}
