#include "GuiSameLine.h"

#include "imgui.h"

jump::system::gui::GuiSameLine::GuiSameLine() : GuiItem()
{
}


jump::system::gui::GuiSameLine::GuiSameLine(GuiItem* parent) : GuiItem(parent)
{
}

jump::system::gui::GuiSameLine::GuiSameLine(GuiItem* parent, const std::string& name) : GuiItem(parent, name)
{
}

jump::system::gui::GuiSameLine::GuiSameLine(GuiItem* parent, const std::string& name, const sf::Vector2f& position) : GuiItem(parent, name, position)
{
}

jump::system::gui::GuiSameLine::GuiSameLine(GuiItem* parent, const std::string& name, const sf::Vector2f& position,
	const sf::Vector2f& size) : GuiItem(parent, name, position, size)
{
}

jump::system::gui::GuiSameLine::GuiSameLine(GuiItem* parent, const std::string& name, const sf::Vector2f& position,
	const sf::Vector2f& size, const flag_t& flags) : GuiItem(parent, name, position, size, flags)
{
}

jump::system::gui::GuiSameLine::GuiSameLine(GuiSameLine& item)
{
	*this = item;
}


jump::system::gui::GuiSameLine::~GuiSameLine()
{
}

jump::system::gui::GuiSameLine& jump::system::gui::GuiSameLine::operator=(const GuiSameLine& item)
{
	auto clone = dynamic_cast<GuiSameLine*>(item.clone());
	*this = std::move(*clone);

	delete clone;
	return *this;
}

jump::system::gui::GuiItem* jump::system::gui::GuiSameLine::clone() const
{
	return dynamic_cast<GuiItem*>(new GuiSameLine(parent(), get_name(), get_position(), get_size(), get_flags()));
}

void jump::system::gui::GuiSameLine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	ImGui::SameLine();
}

