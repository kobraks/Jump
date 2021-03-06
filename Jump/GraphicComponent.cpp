#include "GraphicComponent.h"
#include "lua/lua.hpp"
#include "lua/LuaIntf.h"

jump::component::GraphicComponent::GraphicComponent(entity::Entity* entity, LuaIntf::LuaRef _lua_ref): Component(entity), sprite_(nullptr), texture_(nullptr)
{
}

jump::component::GraphicComponent::GraphicComponent(entity::Entity* entity): Component(entity), sprite_(nullptr), texture_(nullptr)
{
}

jump::component::GraphicComponent::GraphicComponent(): Component(nullptr), sprite_(nullptr), texture_(nullptr)
{
}

jump::component::GraphicComponent::~GraphicComponent()
{
}

void jump::component::GraphicComponent::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	if (sprite_)
		_target.draw(*sprite_, _states);
}

jump::component::Component* jump::component::GraphicComponent::get_copy() const
{
	auto gr = new GraphicComponent();
	if (sprite_)
		gr->sprite_ = new sf::Sprite(*sprite_);
	
	if (texture_)
		gr->texture_ = new sf::Texture(*texture_);

	gr->sprite_->setTexture(*gr->texture_);

	return gr;
}
