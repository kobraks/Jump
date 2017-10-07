#include "GuiForm.h"
#include "imgui.h"

#include "NotInicializedException.h"

#include <iostream>

jump::system::gui::GuiForm::GuiForm() : GuiItem(), main_form_(true), open_(true)
{
}

jump::system::gui::GuiForm::GuiForm(GuiItem* parent) : GuiForm()
{
	GuiForm::set_parent(parent);
}

jump::system::gui::GuiForm::GuiForm(GuiItem* parent, const std::string& name) : GuiForm(parent)
{
	set_name(name);
}

jump::system::gui::GuiForm::GuiForm(GuiItem* parent, const std::string& name, const sf::Vector2f& position) : GuiForm(parent, name)
{
	set_position(position);
}

jump::system::gui::GuiForm::GuiForm(GuiItem* parent, const std::string& name, const sf::Vector2f& position,
	const sf::Vector2f& size) : GuiForm(parent, name, position)
{
	set_size(size);
}

jump::system::gui::GuiForm::GuiForm(GuiItem* parent, const std::string& name, const sf::Vector2f& position,
	const sf::Vector2f& size, const flag_t& flags) : GuiForm(parent, name, position, size)
{
	set_flags(flags);
}

jump::system::gui::GuiForm::GuiForm(GuiForm& gui_form)
{
	*this = gui_form;
}

jump::system::gui::GuiForm::~GuiForm()
{
	for (auto item : items_)
		delete item;

	items_.clear();
}

void jump::system::gui::GuiForm::set_parent(GuiItem* parent)
{
	if (parent == this)
		return;

	for(auto tmp = parent; tmp; tmp = parent->parent())
	{
		if (tmp == this)
			throw std::exception();
		else if (dynamic_cast<GuiForm*>(tmp))
			main_form_ = false;
	}
}

void jump::system::gui::GuiForm::add_item(GuiItem* item)
{
	if (!item || exist(item))
		return;

	item->set_parent(this);
	items_.push_back(item);
}

void jump::system::gui::GuiForm::remove(GuiItem* item)
{
	if (!item)
		return;
	
	auto iterator= std::find(items_.begin(), items_.end(), item);
	if (iterator != items_.end())
		items_.erase(iterator);
}

void jump::system::gui::GuiForm::remove_and_destroy(GuiItem* item)
{
	if (!item)
		return;

	auto iterator = std::find(items_.begin(), items_.end(), item);
	if (iterator != items_.end())
	{
		delete *iterator;
		items_.erase(iterator);
	}
}

bool jump::system::gui::GuiForm::exist(GuiItem* item)
{
	if (!item)
		throw exception::NotInicializedException();

	return std::find(items_.begin(), items_.end(), item) != items_.end();
}

jump::system::gui::GuiItem* jump::system::gui::GuiForm::clone() const
{
	auto result = new GuiForm(parent(), get_name(), get_position(), get_size(), get_flags());

	for (auto item : items_)
		result->items_.push_back(item->clone());

	result->main_form_ = main_form_;
	result->open_ = open_;

	return result;
}

jump::system::gui::GuiForm& jump::system::gui::GuiForm::operator=(const GuiForm& gui_form)
{
	auto clone = gui_form.clone();
	*this = std::move(*dynamic_cast<GuiForm*>(clone));
	delete clone;

	return *this;
}

void jump::system::gui::GuiForm::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (get_position().x >= 0 && get_position().y >= 0)
		ImGui::SetNextWindowPos(get_position());
	else
		ImGui::SetNextWindowPosCenter();
	if (get_size().x != 0 && get_size().y != 0) ImGui::SetNextWindowSize(get_size());

	//std::cout << "position: (" << get_position().x << ", " << get_position().y << ")\n";

	if (main_form_)
		ImGui::Begin(get_name().c_str(), const_cast<bool*>(&open_), static_cast<ImGuiWindowFlags>(translate_flags(get_flags())));
	else
		ImGui::TreeNode(get_name().c_str());

	for (auto item : items_)
		target.draw(static_cast<sf::Drawable&>(*dynamic_cast<sf::Drawable*>(item)), states);

	if (main_form_)
		ImGui::End();
	else
		ImGui::TreePop();
}

int jump::system::gui::GuiForm::translate_flags(const flag_t& flags) const
{
	int result = 0;

	if (GUI_NO_SAVE)
		result |= ImGuiWindowFlags_NoSavedSettings;
	if (GUI_AUTO_RESIZE)
		result |= ImGuiWindowFlags_AlwaysAutoResize;

	return result;
}
