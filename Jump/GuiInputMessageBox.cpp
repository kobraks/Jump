#include "GuiInputMessageBox.h"
#include "GuiButton.h"
#include "GuiManager.h"
#include "ImGui.h"

jump::system::gui::GuiInputMessageBox::GuiInputMessageBox(GuiItem* parent, const std::string& name,
	const std::string& text, const std::string& default_text, const flag_t& flags) : GuiItem(parent), flags_(flags), first_draw_(true)
{
	form_ = new GuiForm(nullptr, name, sf::Vector2f(-1, -1));
	form_->set_flags(GUI_NO_SAVE | GUI_AUTO_RESIZE);
	label_ = new GuiLabel(form_, text);
	input_ = new GuiInputBox(form_, "", default_text);
	input_->flags(ImGuiInputTextFlags_EnterReturnsTrue);
	input_->auto_focus_on_first_draw();

	input_->set_action_on_return_click([this](GuiItem*)
	{
		this->close();
	});

	form_->add(label_);
	form_->add(input_);

	if (flags & YES_BUTTON)
	{
		auto button = new GuiButton(form_, "yes");
		button->set_on_click_action([this](GuiItem*) {button_clicked_ = 1; close(); });
		form_->add(button);
	}
	
	if (flags & NO_BUTTON)
	{
		auto button = new GuiButton(form_, "no");
		button->set_on_click_action([this](GuiItem*) {button_clicked_ = 2; close(); });
		form_->add(button);
	}

	if(flags & IGNORE_BUTTON)
	{
		auto button = new GuiButton(form_, "ignore");
		button->set_on_click_action([this](GuiItem*) {button_clicked_ = 3; close(); });
		form_->add(button);
	}

	GuiManager::add(form_);
}

jump::system::gui::GuiInputMessageBox::~GuiInputMessageBox()
{
	if (GuiManager::exist(form_))
		GuiManager::remove_and_destroy(form_);
	else
		delete form_;
}

void jump::system::gui::GuiInputMessageBox::set_action_on_close(event_function function)
{
	on_close_ = function;
}

void jump::system::gui::GuiInputMessageBox::name(const std::string& name) const
{
	form_->name(name);
}

std::string jump::system::gui::GuiInputMessageBox::name() const
{
	return form_->name();
}

void jump::system::gui::GuiInputMessageBox::text(const std::string& text)
{
	label_->text(text);
}

std::string jump::system::gui::GuiInputMessageBox::text() const
{
	return label_->text();
}

std::string jump::system::gui::GuiInputMessageBox::writed_text() const
{
	return input_->get_text();
}

void jump::system::gui::GuiInputMessageBox::close()
{
	if (on_close_)
		on_close_(this);

	GuiManager::remove(form_);
	first_draw_ = true;
}

int jump::system::gui::GuiInputMessageBox::button_clicked()
{
	return button_clicked_;
}

jump::system::gui::GuiItem* jump::system::gui::GuiInputMessageBox::clone() const
{
	return new GuiInputMessageBox(parent(), form_->name(), label_->text(), input_->get_text(), flags_);
}

void jump::system::gui::GuiInputMessageBox::draw(sf::RenderTarget& target, sf::RenderStates states)
{
}