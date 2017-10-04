#include "GuiForm.h"

#include "imgui.h"

jump::system::gui::GuiForm::GuiForm(GuiItem* parent) : GuiItem(parent), sub_form_(false)
{
}

jump::system::gui::GuiForm::~GuiForm()
{
	for (auto& item : items_)
		delete item;

	items_.clear();
}

void jump::system::gui::GuiForm::add_item(GuiItem* item)
{
	item->set_parent(this);

	items_.push_back(item);
}

void jump::system::gui::GuiForm::remove_item(GuiItem* item)
{
	auto to_remove = std::find(items_.begin(), items_.end(), item);

	if (to_remove != items_.end())
		items_.erase(to_remove);
}

void jump::system::gui::GuiForm::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	bool active = is_active();

	if (sub_form_)
		ImGui::BeginChild(get_name().c_str(), get_size(), border(), get_flags());
	else
		ImGui::Begin(get_name().c_str(), &active);

	for (auto item : items_)
	{
		target.draw(static_cast<sf::Drawable&>(*dynamic_cast<sf::Drawable*>(item)));
	}

	if (sub_form_)
		ImGui::EndChild();
	else
		ImGui::End();
}

void jump::system::gui::GuiForm::set_parent(GuiItem* parent)
{
	for (auto i = parent; i != nullptr; i = parent->parent())
	{
		if (i == this)
			throw std::exception();
		if (dynamic_cast<GuiForm*>(i))
		{
			sub_form_ = true;
			break;
		}
	}
}
