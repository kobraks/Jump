#include "GuiComboBox.h"
#include "BadAllocException.h"
#include "NotInicializedException.h"
#include "OutOfRangeException.h"
#include "imgui.h"

#include <string.h>


jump::system::gui::GuiComboBox::GuiComboBox(GuiItem* parent, const std::string& name, const char*const*items,
	const size_t& items_count, const sf::Vector2f& position) : GuiControl(parent, name, position)
{
	try
	{
		if (items)
			list_ = new List(items, items_count);
		else
			list_ = new List();

	}
	catch(std::bad_alloc)
	{
		throw exception::BadAllocException();
	}
}

jump::system::gui::GuiComboBox::GuiComboBox(const GuiComboBox& combo)
{
	*this = combo;
}

jump::system::gui::GuiComboBox::GuiComboBox(GuiComboBox&& combo) noexcept
{
	*this = std::move(combo);
}

jump::system::gui::GuiComboBox::~GuiComboBox()
{
	delete list_;
}

int jump::system::gui::GuiComboBox::selected() const
{
	return list_->selected();
}

void jump::system::gui::GuiComboBox::add_item(char* item)
{
	if (!item)
		throw exception::NotInicializedException();

	list_->add(item);
}

void jump::system::gui::GuiComboBox::add_item(const std::string& item)
{
	if (item.empty())
		throw exception::NotInicializedException();

	char* buff = new char[item.size() + 1];

	for (std::string::size_type i = 0; i < item.size(); i++)
		buff[i] = item[i];

	buff[item.size() + 1] = '\0';
	
	list_->add(buff);
}

void jump::system::gui::GuiComboBox::set_item(const size_t& index, const std::string& value)
{
	list_->set(index, value.c_str());
}

void jump::system::gui::GuiComboBox::remove_item(const size_t& item)
{
	if (item > list_->size())
		throw exception::OutOfRangeException();

	list_->remove(item);
}

void jump::system::gui::GuiComboBox::remove_item(const std::string& item)
{
	for (size_t i = 0; i < list_->size(); ++i)
	{
		if (item == list_->get(i))
		{
			list_->remove(i);
			return;
		}
	}
}

jump::system::gui::GuiItem* jump::system::gui::GuiComboBox::clone() const
{
	auto result = new GuiComboBox(parent(), name(), list_->items(), list_->size(), position());

	return result;
}

std::string jump::system::gui::GuiComboBox::get(const size_t& item) const
{
	return list_->get(item);
}

std::string jump::system::gui::GuiComboBox::operator[](const size_t& item) const
{
	return list_->get(item);
}

jump::system::gui::GuiComboBox& jump::system::gui::GuiComboBox::operator=(const GuiComboBox& combo)
{
	auto clone = dynamic_cast<GuiComboBox*>(combo.clone());
	*this = std::move(*clone);
	delete clone;
	return *this;
}

jump::system::gui::GuiComboBox& jump::system::gui::GuiComboBox::operator=(GuiComboBox&& combo) noexcept
{
	list_ = combo.list_;
	combo.list_ = nullptr;

	name(combo.name());
	set_parent(combo.parent());
	position(combo.position());

	return *this;
}

void jump::system::gui::GuiComboBox::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	int size = static_cast<int>(list_->size());
	int selected = list_->selected();

	if (position().x >= 0 && position().y >= 0)
		ImGui::SetCursorPos(position());

	ImGui::Combo(name().c_str(), &selected, list_->items(), size);
	list_->set_selected(selected);
}

jump::system::gui::GuiComboBox::List::List(): list_(nullptr), size_(0), selected_(0)
{
}

jump::system::gui::GuiComboBox::List::List(const char*const* list, const size_t& size): size_(size), selected_(0)
{
	list_ = new char*[size];

	for (size_t i = 0; i < size; ++i)
	{
		auto length = strlen(list[i]);

		list_[i] = new char[length];
		strcpy_s(list_[i], length+1, list[i]);
	}
}

jump::system::gui::GuiComboBox::List::~List()
{
	for (size_t i = 0; i < size_; ++i)
		delete[] list_[i];

	delete[] list_;
}

void jump::system::gui::GuiComboBox::List::add(char* item)
{
	if (!item)
		throw exception::NotInicializedException();

	resize(++size_);

	auto length = strlen(item) + 1;
	list_[size_ - 1] = new char[length];
	strcpy_s(list_[size_ - 1], length, item);
}

void jump::system::gui::GuiComboBox::List::remove(const size_t& index)
{
	if (index >= size())
		throw exception::OutOfRangeException();

	resize(--size_, index, false);
}

const char* const* jump::system::gui::GuiComboBox::List::items() const
{
	return list_;
}

const char* jump::system::gui::GuiComboBox::List::get(const size_t& index) const
{
	if (index >= size())
		throw exception::OutOfRangeException();

	return list_[index];
}

void jump::system::gui::GuiComboBox::List::set(const size_t& index, const char* value)
{
	if (index >= size())
		throw exception::OutOfRangeException();

	delete[] list_[index];
	auto length = strlen(value) + 1;

	list_[index] = new char[length];
	strcpy_s(list_[index], length, value);
}

size_t jump::system::gui::GuiComboBox::List::size() const
{
	return size_;
}

int jump::system::gui::GuiComboBox::List::selected() const
{
	return selected_;
}

void jump::system::gui::GuiComboBox::List::set_selected(const int& selected)
{
	selected_ = selected;
}

const char* jump::system::gui::GuiComboBox::List::operator[](const size_t& index) const
{
	return get(index);
}

void jump::system::gui::GuiComboBox::List::resize(const size_t size, const size_t index_to_ignore, bool ignore)
{
	if (!list_)
	{
		list_ = new char*[size];
		return;
	}

	auto tmp = list_;
	list_ = new char*[size];

	for (size_t i = 0; i < size; ++i)
	{
		if (!ignore && i == index_to_ignore)
		{
			delete[] tmp[i];
			continue;
		}
		list_[i] = tmp[i];
		tmp[i] = nullptr;
	}

	delete[] tmp;
}
