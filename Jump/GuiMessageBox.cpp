#include "GuiMessageBox.h"
#include "imgui.h"
#include "GuiForm.h"
#include "GuiButton.h"
#include "GuiLabel.h"

#include "GuiManager.h"
#include "GuiSameLine.h"
#include "BadAllocException.h"

jump::system::gui::GuiMessageBox::GuiMessageBox(GuiItem* parent, const std::string& name, const std::string& text,
	const flag_t& flags) : GuiItem(parent), title_(name)
{
	try
	{
		form_ = new GuiForm(nullptr, name);
		form_->add((label_ = new GuiLabel(nullptr, text)));
		form_->set_flags(GUI_AUTO_RESIZE | GUI_NO_SAVE);


		if (flags & YES_BUTTON)
		{
			auto button = new GuiButton(nullptr, "yes");
			button->set_on_click_action([this](GuiItem*) { button_cliked_ = 1; close(); });

			form_->add(button);
		}
		if (flags & NO_BUTTON)
		{
			if (flags & YES_BUTTON)
				form_->add(new GuiSameLine());

			auto button = new GuiButton(nullptr, "no");
			button->set_on_click_action([this](GuiItem*) { button_cliked_ = 2; close(); });

			form_->add(button);
		}
		if (flags & IGNORE_BUTTON)
		{
			if (flags & NO_BUTTON)
				form_->add(new GuiSameLine());

			auto button = new GuiButton(nullptr, "ignore");
			button->set_on_click_action([this](GuiItem*) { button_cliked_ = 3; close(); });

			form_->add(button);
		}

		form_->position(sf::Vector2f(-1, -1));
		GuiManager::add(form_);
	}
	catch(std::bad_alloc)
	{
		throw exception::BadAllocException();
	}
}

jump::system::gui::GuiMessageBox::GuiMessageBox(const GuiMessageBox& message_box)
{
	*this = message_box;
}

void jump::system::gui::GuiMessageBox::title(const std::string& title)
{
	title_ = title;
}

std::string jump::system::gui::GuiMessageBox::title() const
{
	return title_;
}

void jump::system::gui::GuiMessageBox::text(const std::string& text)
{
	label_->text(text);
}

std::string jump::system::gui::GuiMessageBox::text() const
{
	return label_->text();
}

jump::system::gui::flag_t jump::system::gui::GuiMessageBox::flags() const
{
	return flags_;
}

void jump::system::gui::GuiMessageBox::flags(const flag_t& flags)
{
	flags_ = flags;
}

bool jump::system::gui::GuiMessageBox::yes_clicked() const
{
	return button_cliked_ == 1;
}

bool jump::system::gui::GuiMessageBox::no_clicked() const
{
	return button_cliked_ == 2;
}

bool jump::system::gui::GuiMessageBox::ignore_clicked() const
{
	return button_cliked_ == 3;
}

jump::system::gui::GuiMessageBox::~GuiMessageBox()
{
	close();
	delete form_;
}

jump::system::gui::GuiItem* jump::system::gui::GuiMessageBox::clone() const
{
	auto result = new GuiMessageBox(parent(), title(), label_->text(), flags());
	result->button_cliked_ = button_cliked_;
	GuiManager::remove_and_destroy(result->form_);
	result->form_ = dynamic_cast<GuiForm*>(form_->clone());
	result->form_->remove(label_);
	result->form_->insert(0, label_);
	GuiManager::add(result->form_);

	return result;
}

void jump::system::gui::GuiMessageBox::close() const
{
	GuiManager::remove(form_);
}

void jump::system::gui::GuiMessageBox::show() const
{
	GuiManager::add(form_);
}

jump::system::gui::GuiMessageBox& jump::system::gui::GuiMessageBox::operator=(const GuiMessageBox& message_box)
{
	auto clone = dynamic_cast<GuiMessageBox*>(message_box.clone());
	*this = std::move(*clone);
	delete clone;
	return *this;
}

void jump::system::gui::GuiMessageBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}
