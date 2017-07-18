#pragma once

#include <string>
#include <functional>
#include <list>
#include <SFML/Graphics.hpp>

#include "GuiItem.h"
#include "GuiEvent.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiButton : public GuiItem
			{
			public:
				GuiButton();
				GuiButton(const sf::String& _string, sf::Font& _font, const sf::Vector2f& _position = {0, 0});
				virtual ~GuiButton();

				GuiButton* set_string(const sf::String& _string);
				GuiButton* set_font(sf::Font& _font);
				GuiButton* set_character_size(const sf::Uint16& _size);

				GuiButton* position(const sf::Vector2f& _position);
				GuiButton* position(const float& x, const float& y);
				sf::Vector2f position() const;

				sf::Vector2f size() const;

				void add_action_on_click(std::function<void(sf::Event&, GuiItem*)> _on_click);
				void add_action_on_mouse_enter(std::function<void(sf::Event&, GuiItem*)> _on_mouse_enter);
				void add_action_on_mouse_hover(std::function<void(sf::Event&, GuiItem*)> _on_mouse_hover);
				void add_action_on_mouse_leave(std::function<void(sf::Event&, GuiItem*)> _on_mouse_leave);
				
				void set_texture_clicked(sf::Texture* _texture);
				void set_texture_hovered(sf::Texture* _texture);
				void set_texture_normal(sf::Texture* _texture);

				void set_color_clicked(const sf::Color& _color);
				void set_color_hovered(const sf::Color& _color);
				void set_color_normal(const sf::Color& _color);

				void set_color_text_hovered(const sf::Color& _text_color);
				void set_color_text_clicked(const sf::Color& _text_color);
				void set_color_text_normal(const sf::Color& _text_color);

			private:
				sf::Uint32 state_;

				sf::Text text_;
				sf::RectangleShape rectangle_;

				sf::Texture* texture_clicked_;
				sf::Texture* texture_hovered_;
				sf::Texture* texture_normal_;

				sf::Color color_clicked_;
				sf::Color color_hovered_;
				sf::Color color_normal_;

				sf::Color text_color_clicked_;
				sf::Color text_color_hovered_;
				sf::Color text_color_normal_;

				void update_button();

				virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;
				virtual void update(sf::Event& _e, sf::RenderWindow& _window);

				std::list<std::function<void(sf::Event&, GuiItem*)>> on_clicks_;
				std::list<std::function<void(sf::Event&, GuiItem*)>> on_mouse_enters_;
				std::list<std::function<void(sf::Event&, GuiItem*)>> on_mouse_hovers_;
				std::list<std::function<void(sf::Event&, GuiItem*)>> on_mouse_leaves_;
			};
		}
	}
}
