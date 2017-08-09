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
			explicit GraphicComponent(luabridge::LuaRef& _lua_ref);
			~GraphicComponent();

			void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

		private:
			sf::Sprite* sprite_;
			sf::Texture* texture_;
		};


	}
}
