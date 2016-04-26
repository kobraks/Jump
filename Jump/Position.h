#pragma once

#include <Box2D\Box2D.h>
#include <SFML\System.hpp>

namespace jump
{
	namespace system
	{
		class Position
		{
		public:
			Position();
			Position(const b2Vec2& position);
			Position(const sf::Vector2f& position);

			void set(const sf::Vector2f& position);
			void set(const b2Vec2& position);

			Position& operator=(const b2Vec2& position);
			Position& operator=(const sf::Vector2f& position);

			Position& move(sf::Vector2f& vector);
			Position& move(b2Vec2& vector);

			Position& operator+ (const b2Vec2& vector);
			Position& operator+ (const sf::Vector2f& vector);
			Position& operator+ (const float& number);

			Position& operator- (const b2Vec2& vector);
			Position& operator- (const sf::Vector2f& vector);
			Position& operator- (const float& number);

			Position& operator+= (const b2Vec2& vector);
			Position& operator+= (const sf::Vector2f& vector);
			Position& operator+= (const float& number);

			Position& operator-= (const b2Vec2& vector);
			Position& operator-= (const sf::Vector2f& vector);
			Position& operator-= (const float& number);

			Position& operator*= (const b2Vec2& vector);
			Position& operator*= (const sf::Vector2f& vector);
			Position& operator*= (const float& number);

			Position& operator/= (const b2Vec2& vector);
			Position& operator/= (const sf::Vector2f& vector);
			Position& operator/= (const float& number);

			sf::Vector2f getSFPosition();
			b2Vec2 getBox2dPosition();
		private:
			sf::Vector2f sfml;
			b2Vec2 box2d;
		};
	}
}