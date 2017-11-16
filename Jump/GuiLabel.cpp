#include "GuiLabel.h"

#include "imgui.h"


jump::system::gui::GuiLabel::GuiLabel() : GuiItem()
{
}

jump::system::gui::GuiLabel::GuiLabel(GuiItem* parent) : GuiItem(parent)
{
}

jump::system::gui::GuiLabel::GuiLabel(GuiItem* parent, const std::string& text) : GuiLabel(parent)
{
	text_ = text;
}

jump::system::gui::GuiLabel::GuiLabel(const GuiLabel& label)
{
	*this = label;
}

void jump::system::gui::GuiLabel::text(const std::string& text)
{
	text_ = text;
}

std::string jump::system::gui::GuiLabel::text() const
{
	return text_;
}

jump::system::gui::GuiLabel::~GuiLabel()
{
}

jump::system::gui::GuiItem* jump::system::gui::GuiLabel::clone() const
{
	return new GuiLabel(parent(), text_);
}

jump::system::gui::GuiLabel& jump::system::gui::GuiLabel::operator=(const GuiLabel& label)
{
	auto clone = dynamic_cast<GuiLabel*>(label.clone());
	text_ = std::move(clone->text_);
	move_values(clone);

	delete clone;

	return *this;
}

void jump::system::gui::GuiLabel::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	ImGui::Text(text_.c_str());
}
