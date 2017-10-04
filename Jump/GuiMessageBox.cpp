#include "GuiMessageBox.h"
#include "imgui.h"
#include "GuiForm.h"
#include "GuiButton.h"
#include "GuiLabel.h"

#include "GuiManager.h"

jump::system::gui::GuiMessageBox::GuiMessageBox(GuiItem* _parent, const std::string& name, const std::string& message, const size_t& type): GuiItem(_parent), type_(type)
{
	set_label(message);
	set_name(name);

	_parent->is_active(false);

	form = new GuiForm(this);

	form->add_item(new GuiLabel(form, "text", message));

	if (type_ & YES_BUTTON)
	{
		auto yes_button = new GuiButton("Yes", this);
		form->add_item(yes_button);
	}

	if (type_ & NO_BUTTON)
	{
		auto no_button = new GuiButton("No", this);
		form->add_item(no_button);
	}
	if (type_ & IGNORE_BUTTON)
	{
		auto ignore_button = new GuiButton("Ignore", this);
		form->add_item(ignore_button);
	}

	form->set_name(name);

	GuiManager::add(this);
}

jump::system::gui::GuiMessageBox::~GuiMessageBox()
{
	parent()->is_active(true);
	delete form;
}

void jump::system::gui::GuiMessageBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(static_cast<sf::Drawable&>(*dynamic_cast<sf::Drawable*>(form)), states);
}
