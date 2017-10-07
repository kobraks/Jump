#include "GuiButton.h"

#include "imgui.h"
#include "NotInicializedException.h"

jump::system::gui::GuiButton::GuiButton() : GuiItem()
{
}

jump::system::gui::GuiButton::GuiButton(GuiItem* parent) : GuiItem(parent)
{
}

jump::system::gui::GuiButton::GuiButton(GuiItem* parent, const std::string& name) : GuiItem(parent, name)
{
}

jump::system::gui::GuiButton::GuiButton(GuiItem* parent, const std::string& name, const sf::Vector2f& position) : GuiItem(parent, name, position)
{
}

jump::system::gui::GuiButton::GuiButton(GuiItem* parent, const std::string& name, const sf::Vector2f& position,
	const sf::Vector2f& size) : GuiItem(parent, name, position, size)
{
}

jump::system::gui::GuiButton::GuiButton(GuiItem* parent, const std::string& name, const sf::Vector2f& position,
	const sf::Vector2f& size, const flag_t& flags) : GuiItem(parent, name, position, size, flags)
{
}

jump::system::gui::GuiButton::GuiButton(GuiItem* parent, const std::string& name, const sf::Vector2f& position,
	const sf::Vector2f& size, const flag_t& flags, event_function on_click) : GuiItem(parent, name, position, size, flags)
{
	on_click_ = on_click;
}

jump::system::gui::GuiButton::GuiButton(GuiButton& item)
{
	*this = item;
}

jump::system::gui::GuiButton::~GuiButton()
{
	on_click_ = nullptr;
}

void jump::system::gui::GuiButton::set_on_click_action(event_function on_click)
{
	if (!on_click)
		throw exception::NotInicializedException();

	on_click_ = on_click;
}

jump::system::gui::GuiItem* jump::system::gui::GuiButton::clone() const
{
	return new GuiButton(parent(), get_name(), get_position(), get_size(), get_flags(), on_click_);
}

jump::system::gui::GuiButton& jump::system::gui::GuiButton::operator=(GuiButton& item)
{
	auto clone = dynamic_cast<GuiButton*>(item.clone());
	*this = std::move(*clone);
	delete clone;

	return *this;
}

void jump::system::gui::GuiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (ImGui::Button(get_name().c_str(), get_size()))
		if (on_click_)
			on_click_(this);
}
