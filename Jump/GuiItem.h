#pragma once

#include <functional>
#include "GuiTypes.h"
#include <SFML/Graphics.hpp>

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiManager;

			class GuiItem
			{
			public:
				GuiItem();
				explicit GuiItem(GuiItem* parent);
				GuiItem(GuiItem&) = default;
				GuiItem(GuiItem&&) = default;

				virtual ~GuiItem();

				GuiItem* parent() const;
				virtual void set_parent(GuiItem* parent);

				virtual GuiItem* clone() const = 0;
				
				void set_action_on_draw(std::function<void(GuiItem*)> function_);
				void set_action_on_end_draw(std::function<void(GuiItem*)> function_);;

				void on_draw() const;
				void on_end_draw() const;

				virtual void draw(sf::RenderTarget& target, sf::RenderStates states) = 0;

			protected:
				void copy_values(GuiItem* item);
				void move_values(GuiItem* item);

			private:
				GuiItem* parent_;
				std::function<void(GuiItem*)> on_draw_;
				std::function<void(GuiItem*)> on_end_draw_;

				friend GuiManager;
			};
		}
	}
}

