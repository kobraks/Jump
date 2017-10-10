#include "GuiMenuBar.h"

#include "imgui.h"
#include "GuiMenu.h"
#include "GuiMenuItem.h"
#include "NotInicializedException.h"

jump::system::gui::GuiMenuBar::GuiMenuBar(GuiItem* parent) : GuiItem(parent)
{

}

jump::system::gui::GuiMenuBar::GuiMenuBar(const GuiMenuBar& menu_bar)
{
	*this = menu_bar;
}

void jump::system::gui::GuiMenuBar::add(GuiItem* item)
{
	if (!item)
		throw exception::NotInicializedException();

	if (dynamic_cast<GuiMenu*>(item) || dynamic_cast<GuiMenuItem*>(item))
		GuiItemCointainer::add(item);
	else
		throw std::exception(); //TODO exception
}

jump::system::gui::GuiMenuBar::~GuiMenuBar()
{
	clear();
}

jump::system::gui::GuiItem* jump::system::gui::GuiMenuBar::clone() const
{
	auto result = new GuiMenuBar(parent());
	result->move_items(get_copy());

	return result;
}

jump::system::gui::GuiMenuBar& jump::system::gui::GuiMenuBar::operator=(const GuiMenuBar& menu_bar)
{
	auto clone = dynamic_cast<GuiMenuBar*>(menu_bar.clone());
	*this = std::move(*clone);
	delete clone;

	return *this;
}

void jump::system::gui::GuiMenuBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (ImGui::BeginMainMenuBar())
	{
		for (auto item : get_copy())
			target.draw(static_cast<sf::Drawable&>(*dynamic_cast<sf::Drawable*>(item)), states);

		ImGui::EndMainMenuBar();
	}
}
