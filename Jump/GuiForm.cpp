#include "GuiForm.h"
#include "imgui.h"

jump::system::gui::GuiForm::GuiForm() : GuiControl(), main_form_(true), open_(true), flags_(0)
{
}

jump::system::gui::GuiForm::GuiForm(GuiItem* parent) : GuiForm()
{
	GuiForm::set_parent(parent);
}

jump::system::gui::GuiForm::GuiForm(GuiItem* parent, const std::string& name) : GuiForm(parent)
{
	GuiControl::name(name);
}

jump::system::gui::GuiForm::GuiForm(GuiItem* parent, const std::string& name, const sf::Vector2f& position) : GuiForm(parent, name)
{
	GuiControl::position(position);
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
	clear();
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

void jump::system::gui::GuiForm::set_size(const sf::Vector2f& size)
{
	size_ = size;
}

sf::Vector2f jump::system::gui::GuiForm::get_size() const
{
	return size_;
}

void jump::system::gui::GuiForm::set_flags(const flag_t& flags)
{
	flags_ = flags;
}

jump::system::gui::flag_t jump::system::gui::GuiForm::get_flags() const
{
	return flags_;
}

jump::system::gui::GuiItem* jump::system::gui::GuiForm::clone() const
{
	auto result = new GuiForm(parent(), name(), position(), get_size(), get_flags());
	result->move_items(get_copy());

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
	if (position().x >= 0 && position().y >= 0)
		ImGui::SetNextWindowPos(position());
	else
		ImGui::SetNextWindowPosCenter();
	if (get_size().x != 0 && get_size().y != 0) ImGui::SetNextWindowSize(get_size());

	//std::cout << "position: (" << get_position().x << ", " << get_position().y << ")\n";

	if (main_form_)
		ImGui::Begin(name().c_str(), const_cast<bool*>(&open_), static_cast<ImGuiWindowFlags>(translate_flags(get_flags())));
	else
		ImGui::TreeNode(name().c_str());

	for (auto item : get_items())
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
