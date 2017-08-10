#pragma once

#include "imgui.h"
#include <string>
#include <vector>
#include <fstream>

namespace jump
{
	namespace system
	{
		enum TLogLevel { logERROR, logWARNING, logINFO, logDEBUG, logDEBUG1, logDEBUG2, logDEBUG3, logDEBUG4 };

		class Log
		{
		public:
			Log(Log&) = delete;
			
			static void write_error(const std::string& message, const std::string& error_message = "");
			static void write(const std::string& message, const int& log_level = logINFO);
			static void draw(const char* title, const bool* const p_open);
			static void clear();
			static Log* get_instance();

			~Log();

		private:
			Log();

			std::vector<std::string> text_;
			std::vector<ImVec4> colors_;

			std::fstream file_;

			bool scroll_to_bottom_;
			ImGuiTextFilter filter_;
			unsigned int line_;

			static std::string log_level_to_string(TLogLevel log_level);
			static ImVec4 select_color(const char* message);
			static void add_log(const char* fmt, ...);
			static std::string get_string(const char* fmt, va_list args);
		};
	}
}
