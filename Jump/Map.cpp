#include "Map.h"

#include "NotInicializedException.h"

jump::map::Map::Map()
{
}


jump::map::Map::~Map()
{
}

void jump::map::Map::add_tile(Tile* _tile)
{
	if (_tile)
	{
		if (std::find(tiles_.begin(), tiles_.end(), _tile) == tiles_.end())
			tiles_.push_back(_tile);
	}
	else
		throw system::exception::NotInicializedException();
}

void jump::map::Map::remove_tile(Tile* _tile)
{
	if (_tile)
	{
		auto tile = std::find(tiles_.begin(), tiles_.end(), _tile);

		if (tile != tiles_.end())
		{
			delete *tile;
			tiles_.erase(tile);
		}
	}
	else
		throw system::exception::NotInicializedException();
}

void jump::map::Map::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	for (auto tile : tiles_)
		if (tile->is_visable() && _target.getView().getViewport().intersects(tile->get_global_bounds()))
			_target.draw(const_cast<sf::Drawable&>(*dynamic_cast<sf::Drawable*>(tile)), _states);
}

void jump::map::Map::update(const sf::Event& _event, sf::RenderWindow& _window)
{
	for (auto tile : tiles_)
		if(tile->is_active())
			tile->update(_event, _window);
}

void jump::map::Map::set_word(b2World* _world)
{
	if (_world)
	{
		world_ = _world;
	}
	else
		throw system::exception::NotInicializedException();
}

