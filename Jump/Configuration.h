#pragma once

#include <SFML\Graphics.hpp>

#include <string>
#include <map>

namespace jump
{
	namespace system
	{
		class Configuration
		{
		public:
			Configuration(Configuration&) = delete;
			static Configuration* get_instance();

			virtual ~Configuration();

			void load(const std::string& _file_name);
			void save(const std::string& _file_name);
			void set_defaults();

			std::string font_path;
			std::map <std::string, std::string> font_names;
			std::map <std::string, std::string> loading_textures;
			bool debug, show_fps;

			std::string interface_path;
			std::string textures_path;
			std::string player_textures;
			std::string map_textures;
			std::string data_folder;
			std::string xml_files;
			std::string items_textures;
			std::string hud_textures;
			std::string start_map;

			sf::Uint32 width, height, max_clouds;

			sf::Keyboard::Key up, left, right, down;

			const sf::Time time_step_ = sf::seconds(1.f / 60.f);
		private:
			Configuration();

			static bool read_bool(const std::string& _value, const bool& _default);
			static sf::Uint32 read_int(const std::string& _value, const sf::Uint32& _default);
		};


	}
}