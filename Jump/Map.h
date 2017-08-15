#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <Box2D/Box2D.h>

namespace jump
{
	namespace entity
	{
		class Entity;
	}

	class Map : public sf::Drawable, b2ContactListener
	{
	public:
		Map();
		~Map();
		void update();

		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;

		void add_entity(entity::Entity* entity, const sf::Vector2f& position);
		void remove_entity(entity::Entity* entity);
		void remove_entity_position(entity::Entity* entity, const sf::Vector2f& position);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		b2World* get_world() const;
		void set_world(b2World* world);

		void set_velocityIt(int velocityIt);
		void set_postionIt(int positionIt);
		void clear();
	private:
		class EntityConversion : public sf::Drawable, public sf::Transformable
		{
		public:
			EntityConversion(entity::Entity* entity);
			~EntityConversion();

			void add_position(const sf::Vector2f& position);
			void remove_position(const sf::Vector2f& position);

			std::vector<sf::Vector2f>& get_positions();
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		private:
			entity::Entity* entity_;

			std::vector<sf::Vector2f> positions_;
		};

		void create_conversion(entity::Entity* entity, const sf::Vector2f& position);

		std::unordered_map<entity::Entity*, EntityConversion*> conversions_;
		b2World* world_;
		int velocityIt_, positionIt_;
	};
}
