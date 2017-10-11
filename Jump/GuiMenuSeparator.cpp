#include "GuiMenuSeparator.h"
#include "imgui.h"

jump::system::gui::GuiMenuSeparator::GuiMenuSeparator(GuiItem* parent) : GuiItem(parent)
{
}

jump::system::gui::GuiMenuSeparator::~GuiMenuSeparator()
{
}

jump::system::gui::GuiItem* jump::system::gui::GuiMenuSeparator::clone() const
{
	return new GuiMenuSeparator(parent());
}

void jump::system::gui::GuiMenuSeparator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	ImGui::Separator();
}
