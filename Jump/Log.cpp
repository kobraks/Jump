#include "Log.h"

#include <iostream>

jump::system::Log::Log(): scroll_to_bottom_(false), line_(0), max_log_level_(logDEBUG4)
{
	file_ = std::fstream("log.txt", std::ios::trunc | std::ios::out);
	file_ << "start logging" << std::endl;
}

jump::system::Log* jump::system::Log::get_instance()
{
	static Log instance;
	return &instance;
}


std::string jump::system::Log::log_level_to_string(TLogLevel log_level)
{
	static const char* const buffer[] = { "ERROR", "WARNING", "INFO", "DEBUG", "DEBUG1", "DEBUG2", "DEBUG3", "DEBUG4" };
	//std::cout << static_cast<int>(log_level) << ", " << buffer[static_cast<int>(log_level)] << std::endl;
	return buffer[static_cast<int>(log_level)];
}

ImVec4 jump::system::Log::select_color(const char* message)
{
	if (strstr(message, "[ERROR]"))
		return ImColor(1.0f, 0.4f, 0.4f, 1.0f);
	else if (strstr(message, "WARNING"))
		return ImColor(1.0f, 0.78f, 0.58f, 1.0f);
	else if (strstr(message, "[INFO]"))
		return ImColor(169, 169, 169);
	else
		return ImColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void jump::system::Log::add_log(const char* format, ...)
{
	auto instance = get_instance();
	auto& buffer = instance->text_;
	auto& scroll_to_bottom = instance->scroll_to_bottom_;
	auto& colors = instance->colors_;
	auto& file = instance->file_;

	va_list args;
	va_start(args, format);
	auto text = get_string(format, args);
	va_end(args);
	buffer.push_back(text);
	if (file.good())
		file << text;

	colors.push_back(select_color(text.c_str()));
	std::cout << text;


	scroll_to_bottom = true;
}

std::string jump::system::Log::get_string(const char* format, va_list args)
{
	va_list args_copy;
	va_copy(args_copy, args);

	auto length = vsnprintf(nullptr, 0, format, args);
	if (length <= 0)
		return "";

	auto string = new char[length + 1];
	vsnprintf(string, length + 1, format, args_copy);
	std::string result = string;
	delete[] string;
	return result;
}

void jump::system::Log::set_max_log_level(const TLogLevel& log_level)
{
	get_instance()->max_log_level_ = log_level;
}

jump::system::TLogLevel jump::system::Log::get_max_log_level()
{
	return static_cast<TLogLevel>(get_instance()->max_log_level_);
}

void jump::system::Log::write_error(const std::string& message, const std::string&error_message)
{
	auto instance = get_instance();

	if (instance->max_log_level_ >= logERROR)
	{
		add_log("%u: [%s]: %s\n", instance->line_, log_level_to_string(logERROR).c_str(), message.c_str());
		if (!error_message.empty())
			add_log("error message: %s\n", error_message.c_str());
		instance->colors_[instance->colors_.size() - 1] = ImColor(1.0f, 0.4f, 0.4f, 1.0f);;
		instance->line_++;
	}
}

void jump::system::Log::write(const std::string& message, const int& log_level)
{
	if (get_instance()->max_log_level_ >= log_level)
	{
		add_log("%u: [%s]: %s\n", get_instance()->line_, log_level_to_string(static_cast<TLogLevel>(log_level)).c_str(), message.c_str());
		get_instance()->line_++;
	}
}


void jump::system::Log::draw(const char* title, const bool* const p_open)
{
	auto instance = get_instance();
	auto& filter = instance->filter_;
	auto& texts = instance->text_;
	auto& colors = instance->colors_;
	auto& scroll_to_bottom = instance->scroll_to_bottom_;
	auto& max_log_level = instance->max_log_level_;


	ImGui::SetNextWindowSize(ImVec2(400, 100), ImGuiSetCond_FirstUseEver);
	ImGui::Begin(title, const_cast<bool*>(p_open));
	if (ImGui::Button("clear"))
		clear();
	ImGui::SameLine();
	ImGui::Combo("max log level", &max_log_level, "log error\0log warning\0log info\0log debug\0log debug1\0log debug2\0log debug3\0log debug4");
	auto copy = ImGui::Button("Copy");
	ImGui::SameLine();
	filter.Draw("Filter", -100.0f);
	ImGui::Separator();
	ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
	if (copy) ImGui::LogToClipboard();

	for (size_t i = 0; i < texts.size(); ++i)
	{
		auto text = texts[i].c_str();
		if (!filter.PassFilter(text))
			continue;

		ImGui::PushStyleColor(ImGuiCol_Text, colors[i]);
		ImGui::TextUnformatted(text);
		ImGui::PopStyleColor();
	}

	if (scroll_to_bottom)
		ImGui::SetScrollHere(1.0f);

	scroll_to_bottom = false;
	ImGui::EndChild();
	ImGui::End();
}

void jump::system::Log::clear()
{
	auto instance = get_instance();
	instance->colors_.clear();
	instance->text_.clear();
}

jump::system::Log::~Log()
{
	clear();
	file_.close();
}
