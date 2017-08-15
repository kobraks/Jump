#include "Map.h"

#include "Entity.h"
#include "GraphicComponent.h"
#include "Configuration.h"
#include "BadAllocException.h"
#include "Log.h"

jump::Map::Map(): world_(nullptr), velocityIt_(8), positionIt_(3)
{
}


jump::Map::~Map()
{
	clear();
}

void jump::Map::update()
{
	for (auto entity : conversions_)
	{
		entity.first->get_lua_handler()->update();
	}

	if (world_)
		world_->Step(system::Configuration::get_instance()->time_step_.asSeconds(), velocityIt_, positionIt_);
}

void jump::Map::BeginContact(b2Contact* contact)
{
	for (auto entity : conversions_)
	{
		auto lua_handle = entity.first->get_lua_handler();

		if(entity.first == contact->GetFixtureA()->GetUserData())
		{
			auto entityB = reinterpret_cast<entity::Entity*>(contact->GetFixtureB()->GetUserData());

			system::Log::write("entity \"" + entity.first->get_type() + "\" colide with: \"" + entityB->get_type() +"\"", system::logDEBUG);
			lua_handle->collision(lua_handle, entityB->get_lua_handler());
		}
	}
}

void jump::Map::EndContact(b2Contact* contact)
{
}

void jump::Map::add_entity(entity::Entity* entity, const sf::Vector2f& position)
{
	auto find = conversions_.find(entity);
	if (find != conversions_.end())
	{
		if (conversions_[entity])
			conversions_[entity]->add_position(position);
		else
			create_conversion(entity, position);
	}
	else
		create_conversion(entity, position);
}

void jump::Map::remove_entity(entity::Entity* entity)
{
	auto find = conversions_.find(entity);
	if (find != conversions_.end())
	{
		delete find->second;
		find->second = nullptr;
	}
}

void jump::Map::remove_entity_position(entity::Entity* entity, const sf::Vector2f& position)
{
	auto find = conversions_.find(entity);
	if (find != conversions_.end())
	{
		find->second->remove_position(position);
	}
}

void jump::Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(auto entity_conversion : conversions_)
	{
		for (auto position : entity_conversion.second->get_positions())
		{
			entity_conversion.second->setPosition(position);
			target.draw(*entity_conversion.second, states);
		}
	}
}

b2World* jump::Map::get_world() const
{
	return world_;
}

void jump::Map::set_world(b2World* world)
{
	delete world_;
	world_ = world;
	world_->SetContactListener(this);
}

void jump::Map::set_velocityIt(int velocityIt)
{
	velocityIt_ = velocityIt;
}

void jump::Map::set_postionIt(int positionIt)
{
	positionIt_ = positionIt;
}

void jump::Map::clear()
{
	for (auto conversion : conversions_)
	{
		delete conversion.second;
	}

	conversions_.clear();
}

jump::Map::EntityConversion::EntityConversion(entity::Entity* entity) : entity_(entity)
{
}

jump::Map::EntityConversion::~EntityConversion()
{
	entity_ = nullptr;
	positions_.clear();
}

void jump::Map::EntityConversion::add_position(const sf::Vector2f& position)
{
	positions_.push_back(position);
}

void jump::Map::EntityConversion::remove_position(const sf::Vector2f& position)
{
	for (unsigned int i = 0; i < positions_.size(); ++i)
	{
		if (positions_[i] == position)
		{
			positions_.erase(positions_.begin() + i);
			return;
		}
	}
}

std::vector<sf::Vector2f>& jump::Map::EntityConversion::get_positions()
{
	return positions_;
}

void jump::Map::EntityConversion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto gr = entity_->get_component<component::GraphicComponent>();
	if (gr)
	{
		states.transform *= getTransform();
		target.draw(*gr, states);
	}
	else
		system::Log::write_error("this entity has no graphiccomponent to draw");
}

void jump::Map::create_conversion(entity::Entity* entity, const sf::Vector2f& position)
{
	try
	{
		auto entity_conversion = new EntityConversion(entity);
		entity_conversion->add_position(position);
		conversions_[entity] = entity_conversion;
	}
	catch(std::bad_alloc)
	{
		throw system::exception::BadAllocException();
	}
}
