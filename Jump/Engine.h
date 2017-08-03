#pragma once

#include "Menu.h"
#include "Map.h"

namespace jump
{
	class Engine : public Menu
	{
	public:
		Engine(Menu* _parent = nullptr);
		~Engine();

		virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;

	protected:
		virtual void update(const sf::Event& _event, sf::RenderWindow& _window);
		
	private:
		Map* map_;
	};
}
