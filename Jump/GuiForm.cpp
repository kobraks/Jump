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

bool jump::system::gui::GuiForm::is_open() const
{
	return open_;
}

void jump::system::gui::GuiForm::close()
{
	open_ = false;
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
	auto clone = dynamic_cast<GuiForm*>(gui_form.clone());
	move_values(clone);
	main_form_ = std::move(clone->main_form_);
	open_ = std::move(clone->open_);

	position(clone->position());
	set_size(clone->get_size());
	set_flags(clone->get_flags());
	name(clone->name());

	move_items(clone->get_items());

	delete clone;

	return *this;
}

void jump::system::gui::GuiForm::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	if (position().x >= 0 && position().y >= 0 && !(GUI_FORCE_MIDDLE_POSITION & flags_))
		ImGui::SetNextWindowPos(position());
	else
		ImGui::SetNextWindowPosCenter();
	if (get_size().x < 0 && get_size().y < 0) ImGui::SetNextWindowSize(get_size());

	//std::cout << "position: (" << get_position().x << ", " << get_position().y << ")\n";

	//if (main_form_)
		ImGui::Begin(name().c_str(), const_cast<bool*>(&open_), static_cast<ImGuiWindowFlags>(translate_flags(get_flags())));
	//else
		//ImGui::TreeNode(name().c_str());

	draw_items(target, states);

	//if (main_form_)
		ImGui::End();
	//else
		//ImGui::TreePop();
}

int jump::system::gui::GuiForm::translate_flags(const flag_t& flags) const
{
	int result = 0;

	if (GUI_NO_SAVE & flags)
		result |= ImGuiWindowFlags_NoSavedSettings;
	if (GUI_AUTO_RESIZE & flags)
		result |= ImGuiWindowFlags_AlwaysAutoResize;
	if (GUI_NO_TITLE_BAR & flags)
		result |= ImGuiWindowFlags_NoTitleBar;
	return result;
}
