#include "GuiLabel.h"

#include "imgui.h"


jump::system::gui::GuiLabel::GuiLabel() : GuiItem()
{
}

jump::system::gui::GuiLabel::GuiLabel(GuiItem* parent) : GuiItem(parent)
{
}

jump::system::gui::GuiLabel::GuiLabel(GuiItem* parent, const std::string& text) : GuiItem(parent, text)
{
}

jump::system::gui::GuiLabel::GuiLabel(GuiItem* parent, const std::string& text, const sf::Vector2f& position) : GuiItem(parent, text, position)
{
}

jump::system::gui::GuiLabel::GuiLabel(GuiItem* parent, const std::string& text, const sf::Vector2f& position,
	const sf::Vector2f& size) : GuiItem(parent, text, position, size)
{
}

jump::system::gui::GuiLabel::GuiLabel(GuiItem* parent, const std::string& text, const sf::Vector2f& position,
	const sf::Vector2f& size, const flag_t& flags) : GuiItem(parent, text, position, size, flags)
{
}

jump::system::gui::GuiLabel::GuiLabel(const GuiLabel& label)
{
	*this = label;
}

jump::system::gui::GuiLabel::~GuiLabel()
{
}

jump::system::gui::GuiItem* jump::system::gui::GuiLabel::clone() const
{
	return new GuiLabel(parent(), get_name(), get_position(), get_size(), get_flags());
}

jump::system::gui::GuiLabel& jump::system::gui::GuiLabel::operator=(const GuiLabel& label)
{
	auto clone = dynamic_cast<GuiLabel*>(label.clone());
	*this = std::move(*clone);
	delete clone;

	return *this;
}

void jump::system::gui::GuiLabel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	ImGui::Text(get_name().c_str());
}
