#pragma once
#include "Component.h"
#include <SFML/Graphics/Drawable.hpp>

namespace sf
{
	class Sprite;
}

namespace jump
{
	namespace component
	{
		class GraphicComponent : public Component, public sf::Drawable
		{
		public:
			GraphicComponent(luabridge::luaRef* _lua_ref);
			~GraphicComponent();

			void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

		private:
			sf::Sprite* sprite_;
		};


	}
}
