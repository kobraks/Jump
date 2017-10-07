#include "GuiInputBox.h"
#include "imgui.h"
#include "BadAllocException.h"

jump::system::gui::GuiInputBox::GuiInputBox()
{
	try
	{
		size_ = 1;
		buffer_ = new char [size_];
		buffer_[0] = '\0';
	}
	catch(std::bad_alloc)
	{
		throw exception::BadAllocException();
	}
}

jump::system::gui::GuiInputBox::GuiInputBox(GuiItem* parent) : GuiInputBox()
{
	GuiItem::set_parent(parent);
}

jump::system::gui::GuiInputBox::GuiInputBox(GuiItem* parent, const std::string& text) : GuiInputBox(parent)
{
	set_name(text);
	size_ = text.size();
	delete[] buffer_;

	try
	{
		buffer_ = new char[size_+1];
		std::copy(text.begin(), text.end(), buffer_);
		buffer_[size_ - 1] = '\0';
	}
	catch(std::bad_alloc)
	{
		throw exception::BadAllocException();
	}
}

jump::system::gui::GuiInputBox::GuiInputBox(GuiItem* parent, const std::string& text, const sf::Vector2f& position) : GuiInputBox(parent, text)
{
	set_position(position);
}

jump::system::gui::GuiInputBox::GuiInputBox(GuiItem* parent, const std::string& text, const sf::Vector2f& position,
	const sf::Vector2f& size) : GuiInputBox(parent, text, position)
{
	set_size(size);
}

jump::system::gui::GuiInputBox::GuiInputBox(GuiItem* parent, const std::string& text, const sf::Vector2f& position,
	const sf::Vector2f& size, const flag_t& flags) : GuiInputBox(parent, text, position, size)
{
	set_flags(flags);
}

jump::system::gui::GuiInputBox::GuiInputBox(const GuiInputBox& input)
{
	*this = input;
}

jump::system::gui::GuiInputBox::GuiInputBox(GuiInputBox&& input) noexcept
{
	*this = std::move(input);
}


jump::system::gui::GuiInputBox::~GuiInputBox()
{
	delete[] buffer_;
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
	set_name(input.get_name());
	set_size(input.get_size());
	set_parent(input.parent());
	set_flags(input.get_flags());
	set_position(input.get_position());

	buffer_ = input.buffer_;
	input.buffer_ = nullptr;
	size_ = input.size_;

	return*this;
}

void jump::system::gui::GuiInputBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	ImGui::InputText(get_name().c_str(), buffer_, size_);
	text_ = std::string(buffer_);
	extend_buffer();
}
