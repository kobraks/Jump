#include "GuiButton.h"



jump::system::gui::GuiButton::GuiButton(): state_(0), texture_clicked_(nullptr), texture_hovered_(nullptr), texture_normal_(nullptr)
{
}

jump::system::gui::GuiButton::GuiButton(const sf::String& _string, sf::Font& _font, const sf::Vector2f& _position) : GuiButton()
{
	set_string(_string);
	set_font(_font);
	position(_position);
}

jump::system::gui::GuiButton::~GuiButton()
{
	on_clicks_.clear();
	on_mouse_enters_.clear();
	on_mouse_hovers_.clear();
	on_mouse_leaves_.clear();
}

void jump::system::gui::GuiButton::update(sf::Event& _e, sf::RenderWindow& _window)
{
	auto mouse_position = sf::Mouse::getPosition(_window);

	bool mouse_insite;

	if (_e.type == sf::Event::MouseMoved)
	{
		if (mouse_insite && state_ == state::hovered)
		{
			for (auto function : on_mouse_hovers_)
				function(_e, this);

			state_ = state::hovered;
		}
		else if(mouse_insite)
		{
			for (auto function : on_mouse_enters_)
				function(_e, this);

			state_ = state::hovered;
		}
		else if(state_ == state::hovered)
		{
			for (auto function : on_mouse_leaves_)
				function(_e, this);

			state_ = state::normal;
		}
	}

	if (_e.type == sf::Event::MouseButtonPressed)
	{
		if (mouse_insite)
		{
			for (auto function : on_clicks_)
				function(_e, this);

			state_ = state::clicked;
		}
		else
		{
			state_ = state::normal;
		}
	}

	if (_e.type == sf::Event::MouseButtonReleased)
	{
		if (mouse_insite)
		{
			state_ = state::hovered;
		}
		else
			state_ = state::normal;
	}

	switch(state_)
	{
	case state::normal:

		break;
	}
}

