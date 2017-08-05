#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>

#include <queue>

namespace jump
{
	class Menu : public sf::Drawable
	{
	public:
		explicit Menu(Menu* parent);
		virtual ~Menu();

		Menu* perent() const;
		bool is_running() const;
		void stop();

		virtual void update(sf::RenderWindow& window);

		static void register_event(const sf::Event& event);
		static void clear_events();
		static std::queue<sf::Event>& get_events();
	protected:
		virtual void update(const sf::Event& event, sf::RenderWindow& window) = 0;
	private:
		bool run_;
		Menu* parent_;

		class Events
		{
			std::queue<sf::Event> events_;
			Events();
			static Events* get_instance();

		public:
			static void register_event(const sf::Event& event);
			static void clear_event();
			static std::queue<sf::Event>& get_events();
		};
	};

}
