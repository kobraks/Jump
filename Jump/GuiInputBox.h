#pragma once

#include <functional>
#include "GuiItem.h"
#include "GuiTypes.h"
#include "GuiControl.h"
#include "imgui.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiInputBox : public GuiControl
			{
			public:
				GuiInputBox(GuiItem* parent = nullptr, const std::string& name = "", const std::string& text = "", const sf::Vector2f& position = sf::Vector2f(-1, -1));
				GuiInputBox(const GuiInputBox& input);
				GuiInputBox(GuiInputBox&& input) noexcept;

				void set_action_on_return_click(event_function on_return_click);
				void set_action_on_key_click(event_function on_key_click);

				void flags(const ImGuiInputTextFlags& flags);
				ImGuiInputTextFlags flags() const;

				void auto_focus_on_first_draw();

				~GuiInputBox() override;

				GuiItem* clone() const override;

				std::string get_text() const;

				GuiInputBox& operator= (const GuiInputBox& input);
				GuiInputBox& operator=(GuiInputBox&& input) noexcept;
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) override;

			private:
				class Buffer
				{
				public:
					explicit Buffer(const std::string& string);
					explicit Buffer(const size_t& size);

					std::string get_text() const;
					void set_text(const std::string& string);

					size_t get_size() const;
					void set_size(const size_t& size);

					char* get_buffer() const;


				private:
					char* buffer_;
					size_t size_;
				} *buffer_;

				event_function on_enter_;
				event_function on_key_click_;

				ImGuiInputTextFlags flags_;

				bool auto_focus_;
			};
		}
	}
}

