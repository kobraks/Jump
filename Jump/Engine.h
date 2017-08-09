#pragma once

#include <vector>

#include "Menu.h"
#include "Entity.h"

namespace jump
{
	class Engine : public Menu
	{
	public:
		Engine(Menu* _parent = nullptr);
		~Engine();

		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
		void update(sf::RenderWindow& window) override;
	};
}
