#include "GuiSameLine.h"

#include "imgui.h"

jump::system::gui::GuiSameLine::GuiSameLine() : GuiItem()
{
}


jump::system::gui::GuiSameLine::GuiSameLine(GuiItem* parent) : GuiItem(parent)
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

	move_values(clone);

	delete clone;
	return *this;
}

jump::system::gui::GuiItem* jump::system::gui::GuiSameLine::clone() const
{
	return dynamic_cast<GuiItem*>(new GuiSameLine(parent()));
}

void jump::system::gui::GuiSameLine::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	ImGui::SameLine();
}

