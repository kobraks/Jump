#include "GuiButton.h"

#include "imgui.h"
#include "NotInicializedException.h"


jump::system::gui::GuiButton::GuiButton(GuiItem* parent, const std::string& name, const sf::Vector2f& position,
	const sf::Vector2f& size, event_function on_click) : GuiControl(parent, name, position)
{
	size_ = size;
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

void jump::system::gui::GuiButton::size(const sf::Vector2f& size)
{
	size_ = size;
}

sf::Vector2f jump::system::gui::GuiButton::size() const
{
	return size_;
}

void jump::system::gui::GuiButton::set_on_click_action(event_function on_click)
{
	if (!on_click)
		throw exception::NotInicializedException();

	on_click_ = on_click;
}

jump::system::gui::GuiItem* jump::system::gui::GuiButton::clone() const
{
	return new GuiButton(parent(), name(), position(), size(), on_click_);
}

jump::system::gui::GuiButton& jump::system::gui::GuiButton::operator=(GuiButton& item)
{
	auto clone = dynamic_cast<GuiButton*>(item.clone());
	on_click_ = std::move(clone->on_click_);
	size_ = std::move(clone->size_);
	move_values(clone);

	delete clone;

	return *this;
}

void jump::system::gui::GuiButton::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	if (position().x >= 0 && position().y >= 0)
		ImGui::SetCursorPos(position());

	if (ImGui::Button(name().c_str(), size()))
		if (on_click_)
			on_click_(const_cast<GuiButton*>(this));
}