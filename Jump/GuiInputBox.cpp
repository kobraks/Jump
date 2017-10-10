#include "GuiInputBox.h"
#include "imgui.h"
#include "BadAllocException.h"


jump::system::gui::GuiInputBox::GuiInputBox(GuiItem* parent, const std::string& name, const std::string& text,
	const sf::Vector2f& position) : GuiControl(parent, name, position)
{
	try
	{
		buffer_ = new Buffer(text);
	}
	catch(std::bad_alloc)
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

void jump::system::gui::GuiInputBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (position().x > 0 && position().y > 0)
		ImGui::SetCursorPos(position());

	ImGui::InputText(name().c_str(), buffer_->get_buffer(), buffer_->size());
	buffer_->set_text(buffer_->get_text());
}

jump::system::gui::GuiInputBox::Buffer::Buffer(const std::string& text) : Buffer(text.size() + 1)
{
	std::copy(text.begin(), text.end(), buffer_);
	buffer_[size_ - 1] = '\0';
}

jump::system::gui::GuiInputBox::Buffer::Buffer(const size_t& size) : buffer_(new char[size]), size_(size)
{
	buffer_[0] = '\0';
}

jump::system::gui::GuiInputBox::Buffer::Buffer(const Buffer& buffer)
{
	*this = buffer;
}

jump::system::gui::GuiInputBox::Buffer::Buffer(Buffer&& buffer) noexcept
{
	*this = std::move(buffer);
}

jump::system::gui::GuiInputBox::Buffer& jump::system::gui::GuiInputBox::Buffer::operator=(const Buffer& buffer)
{
	resize(buffer.size());

	std::copy(buffer.buffer_, buffer.buffer_ + buffer.size_, buffer_);

	return *this;
}

jump::system::gui::GuiInputBox::Buffer& jump::system::gui::GuiInputBox::Buffer::operator=(Buffer&& buffer) noexcept
{
	size_ = buffer.size_;
	buffer_ = buffer.buffer_;
	buffer.buffer_ = nullptr;

	return *this;
}

jump::system::gui::GuiInputBox::Buffer::~Buffer()
{
	delete[] buffer_;
}

char* jump::system::gui::GuiInputBox::Buffer::get_buffer() const
{
	return buffer_;
}

size_t jump::system::gui::GuiInputBox::Buffer::size() const
{
	return size_;
}

void jump::system::gui::GuiInputBox::Buffer::set_text(const std::string& text)
{
	resize(text.size() + 1);
	std::copy(text.begin(), text.end(), buffer_);
	buffer_[size_ - 1] = '\0';
}

std::string jump::system::gui::GuiInputBox::Buffer::get_text() const
{
	return std::string(buffer_);
}

void jump::system::gui::GuiInputBox::Buffer::resize(const size_t& size)
{
	delete[] buffer_;
	buffer_ = new char[size];
	size_ = size;
}
