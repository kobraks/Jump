#pragma once

#include <queue>
#include <SFML/Graphics.hpp>

namespace jump
{
	class Menu : public sf::Drawable
	{
	public:

		Menu(Menu* _parent) : parent_(_parent), run_(true)
		{
		}

		virtual ~Menu()
		{
			parent_ = nullptr;
		}

		Menu* parent() const
		{
			return parent_;
		}

		virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const = 0;
		
		bool is_running() const
		{
			return run_;
		}

		void stop()
		{
			run_ = false;
		}

		void update(sf::RenderWindow& _window)
		{
			if (is_running())
			{
				update(events_.front(), _window);
				events_.pop();
			}
		}

		void add_event(sf::Event& _event)
		{
			events_.push(_event);
		}

	protected:
		virtual void update(sf::Event& _event, sf::RenderWindow& _window) = 0;

	private:
		Menu* parent_;
		std::queue<sf::Event> events_;
		bool run_;
	};

}
