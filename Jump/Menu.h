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
			events_ = Events::get_events();

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
			Events::register_event(_event);
		}

		void clear_events()
		{
			Events::clear_events();
		}

	protected:
		virtual void update(sf::Event& _event, sf::RenderWindow& _window) = 0;

	private:
		Menu* parent_;
		std::queue<sf::Event> events_;

		class Events
		{
			std::queue<sf::Event> events_;

			Events()
			{}

			static Events* get_instace()
			{
				static Events instance;

				return &instance;
			}

		public:
			static void register_event(const sf::Event& _event)
			{
				auto instance = get_instace();

				instance->events_.push(_event);
			}

			static void clear_events()
			{
				auto instance = get_instace();

				while (!instance->events_.empty())
					instance->events_.pop();
			}

			static std::queue<sf::Event>& get_events()
			{
				auto instance = get_instace();

				return instance->events_;
			}

		};
		bool run_;
	};

}
