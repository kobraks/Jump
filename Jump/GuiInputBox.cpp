#include "GuiInputBox.h"
#include "imgui.h"
#include "BadAllocException.h"
#include "defines.h"
#include <iostream>
#include <cstdlib>

#define MAX_BUFFER_SIZE 256

jump::system::gui::GuiInputBox::GuiInputBox(GuiItem* parent, const std::string& name, const std::string& text,
	const sf::Vector2f& position) : GuiControl(parent, name, position), flags_(0)
{
	try
	{
		buffer_ = new Buffer(text);
	}
	catch (std::bad_alloc)
	{
		throw exception::BadAllocException();
	}
}

jump::system::gui::GuiInputBox::GuiInputBox(const GuiInputBox& input)
{
	*this = input;
}

jump::system::gui::GuiInputBox::GuiInputBox(GuiInputBox&& input) noexcept
{
	*this = std::move(input);
}

void jump::system::gui::GuiInputBox::set_action_on_return_click(event_function on_return_click)
{
	on_enter_ = on_return_click;
}

void jump::system::gui::GuiInputBox::set_action_on_key_click(event_function on_key_click)
{
	on_key_click_ = on_key_click;
}

void jump::system::gui::GuiInputBox::flags(const ImGuiInputTextFlags& flags)
{
	flags_ = flags;
}

ImGuiInputTextFlags jump::system::gui::GuiInputBox::flags() const
{
	return flags_;
}

void jump::system::gui::GuiInputBox::auto_focus_on_first_draw()
{
	auto_focus_ = true;
}

jump::system::gui::GuiInputBox::~GuiInputBox()
{
	delete buffer_;
}

jump::system::gui::GuiItem* jump::system::gui::GuiInputBox::clone() const
{
	return new GuiInputBox(parent(), name(), buffer_->get_text(), position());
}

std::string jump::system::gui::GuiInputBox::get_text() const
{
	return buffer_->get_text();
}

jump::system::gui::GuiInputBox& jump::system::gui::GuiInputBox::operator=(const GuiInputBox& input)
{
	auto clone = dynamic_cast<GuiInputBox*>(input.clone());
	*this = std::move(*clone);
	delete clone;
	return *this;
}

jump::system::gui::GuiInputBox& jump::system::gui::GuiInputBox::operator=(GuiInputBox&& input) noexcept
{
	set_parent(input.parent());
	name(input.name());
	position(input.position());

	buffer_ = input.buffer_;
	input.buffer_ = nullptr;

	return*this;
}

void jump::system::gui::GuiInputBox::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	if (position().x > 0 && position().y > 0)
		ImGui::SetCursorPos(position());
	//ImGui::SetKeyboardFocusHere();
	
	if (auto_focus_)
		if (ImGui::IsRootWindowFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0))
			ImGui::SetKeyboardFocusHere();

	if (ImGui::InputText(name().c_str(), buffer_->get_buffer(), buffer_->get_size(), flags_))
	{
		if (flags_ & ImGuiInputTextFlags_EnterReturnsTrue && on_key_click_)
			on_key_click_(dynamic_cast<GuiItem*>(const_cast<GuiInputBox*>(this)));

		if (flags_ & ImGuiInputTextFlags_EnterReturnsTrue)
			on_enter_(const_cast<GuiInputBox*>(this));
	}
	buffer_->set_text(buffer_->get_text());
}

jump::system::gui::GuiInputBox::Buffer::Buffer(const std::string& string) : Buffer(string.size() + 1)
{
	sprintf_s(buffer_, size_, "%s", string.c_str());
}

jump::system::gui::GuiInputBox::Buffer::Buffer(const size_t& size)
{
	set_size(size);
}

std::string jump::system::gui::GuiInputBox::Buffer::get_text() const
{
	std::string s(buffer_);
	return s;
}

void jump::system::gui::GuiInputBox::Buffer::set_text(const std::string& string)
{
	sprintf_s(buffer_, size_, "%s", string.c_str());
}

size_t jump::system::gui::GuiInputBox::Buffer::get_size() const
{
	return size_;
}

void jump::system::gui::GuiInputBox::Buffer::set_size(const size_t& size)
{
	if (size > MAX_BUFFER_SIZE)
		size_ = size;
	else
		size_ = MAX_BUFFER_SIZE;

	try
	{
		buffer_ = new char[size_];
		std::fill(buffer_, buffer_ + size_, 0);
	}
	catch (std::bad_alloc&)
	{
		throw exception::BadAllocException();
	}
}

char* jump::system::gui::GuiInputBox::Buffer::get_buffer() const
{
	return buffer_;
}