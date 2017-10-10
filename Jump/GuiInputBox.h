#pragma once

#include "GuiItem.h"
#include "GuiTypes.h"
#include "GuiControl.h"

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

				~GuiInputBox() override;

				GuiItem* clone() const override;

				std::string get_text() const;

				GuiInputBox& operator= (const GuiInputBox& input);
				GuiInputBox& operator=(GuiInputBox&& input) noexcept;
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			private:
				class Buffer
				{
				public:
					explicit Buffer(const std::string& text);
					explicit Buffer(const size_t& size);
					Buffer(const Buffer& buffer);
					Buffer(Buffer&& buffer) noexcept;

					Buffer& operator=(const Buffer& buffer);
					Buffer& operator=(Buffer&& buffer) noexcept;

					~Buffer();

					char* get_buffer() const;
					size_t size() const;

					void set_text(const std::string& text);
					std::string get_text() const;

					void resize(const size_t& size);

				private:
					char* buffer_;
					size_t size_;
				} *buffer_;
			};
		}
	}
}

