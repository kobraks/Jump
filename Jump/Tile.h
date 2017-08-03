#pragma once
#include  <SFML/Graphics.hpp>

#include "Box2D/Box2D.h"
#include "NotInicializedException.h"

namespace jump
{
	class Map;

	namespace map
	{
		class Tile : public sf::Drawable
		{
		public:
			explicit Tile(Tile* _parent): body_(nullptr), parent_(_parent), active_(true), visable_(true)
			{
			}

			virtual ~Tile()
			{
				parent_ = nullptr;
			}

			virtual void update(const sf::Event& _event, sf::RenderWindow& _window) = 0;
			virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const = 0;

			void is_active(const bool& _active)
			{
				active_ = _active;
			}

			bool is_active() const
			{
				return active_;
			}

			bool is_visable() const
			{
				return visable_;
			}

			void is_visable(const bool& _visalbe)
			{
				visable_ = _visalbe;
			}

			sf::Vector2f get_position() const
			{
				return position_;
			}

			virtual void set_position(const sf::Vector2f& _position)
			{
				position_ = _position;
			}

			const sf::FloatRect get_global_bounds() const
			{
				return sprite_.getGlobalBounds();
			}

			b2Body* get_body() const
			{
				return body_;
			}

			void set_body(b2Body* _body)
			{
				if (_body)
					body_ = _body;
				else
					throw system::exception::NotInicializedException();
			}

			sf::Sprite& get_spirte()
			{
				return sprite_;
			}

			sf::Sprite get_sprite() const
			{
				return sprite_;
			}

			void set_sprite(const sf::Sprite& _sprite)
			{
				sprite_ = _sprite;
			}

			void set_texture(const sf::Texture* _texture, sf::IntRect _texture_rectange)
			{
				sprite_.setTexture(*_texture);
				sprite_.setTextureRect(_texture_rectange);
			}

		protected:
			b2Body* body_;
			sf::Sprite sprite_;

		private:
			friend Map;
			Tile* parent_;

			bool active_;
			bool visable_;

			sf::Vector2f position_;
		};
	}
}

