#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>


namespace jump
{
	namespace component
	{
		class GraphicComponent : public Component, public sf::Drawable
		{
		public:
			GraphicComponent();
			GraphicComponent(entity::Entity* entity, LuaIntf::LuaRef _lua_ref);
			explicit GraphicComponent(entity::Entity* entity);
			~GraphicComponent();

			void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

			Component* get_copy() const override;
		private:
			sf::Sprite* sprite_;
			sf::Texture* texture_;
		};


	}
}
