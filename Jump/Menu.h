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
			if (events_.empty())
			{
				update(sf::Event(), _window);
			}

			while (!events_.empty())
			{
				update(events_.front(), _window);
				events_.pop();
				if (!is_running())
					break;
			}
		}

		void register_event(const sf::Event& _event)
		{
			events_.push(_event);
		}

		void clear_events()
		{
			while (!events_.empty())
				events_.pop();
		}

	protected:
		virtual void update(sf::Event& _event, sf::RenderWindow& _window) = 0;

	private:
		Menu* parent_;
		std::queue<sf::Event> events_;
		bool run_;
	};

}
