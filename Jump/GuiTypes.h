#pragma once
#include <functional>

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiItem;

			typedef size_t flag_t;
			typedef std::function<void(GuiItem*)> event_function;

		}
	}
}
