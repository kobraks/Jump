#include "GuiLabel.h"

#include "imgui.h"

jump::system::gui::GuiLabel::GuiLabel(GuiItem* _parent, const std::string& name, const std::string& text) : GuiItem(_parent)
{
	set_name(name);
	set_label(text);
}


jump::system::gui::GuiLabel::~GuiLabel()
{
}

void jump::system::gui::GuiLabel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Vector2f position = ImGui::GetCursorPos();

	ImGui::SetCursorPos(get_position());
	ImGui::Text(get_label().c_str());

	ImGui::SetCursorPos(position);
}
