#pragma once
#include "GuiItem.h"

namespace jump
{
	namespace system
	{
		namespace gui
		{
			class GuiComboBox : public GuiItem
			{
			public:
				GuiComboBox(GuiItem* parent, const std::string& name);
				GuiComboBox(GuiItem* parent, const std::string& name, char** items, const size_t& items_count);
				GuiComboBox(GuiItem* parent, const std::string& name, char** items, const size_t& items_count, const sf::Vector2f& position);
				GuiComboBox(const GuiComboBox& combo);
				GuiComboBox(GuiComboBox&& combo) noexcept;

				~GuiComboBox();

				int selected() const;

				void add_item(char* item);
				void add_item(const std::string& item);
				
				void set_item(const size_t& index, const std::string& value);

				void remove_item(const size_t& item);
				void remove_item(char* item);
				void remove_item(const std::string& item);

				GuiItem* clone() const override;

				std::string get(const size_t& item) const;
				std::string operator[](const size_t& item) const;

				GuiComboBox& operator= (const GuiComboBox& combo);
				GuiComboBox& operator= (GuiComboBox&& combo) noexcept;
			protected:
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			private:
				class List
				{
				public:
					List();
					List(char** list, const size_t& size);

					~List();

					void add(char* item);
					void remove(const size_t& index);

					const char* const* items() const;
					const char* get(const size_t& index) const;

					void set(const size_t& index, const char* value);

					size_t size() const;

					int selected() const;
					void set_selected(const int& selected);

					const char* operator[](const size_t& index) const;
				private:
					char** list_;
					size_t size_;

					int selected_;

					void resize(const size_t size, const size_t index_to_ignore = 0, bool ignore = true); 
				} *list_;

			};
		}
	}
}
