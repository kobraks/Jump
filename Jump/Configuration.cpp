#include "Configuration.h"

#include <boost/algorithm/string.hpp>

#include "defines.h"

#include "INIFile.h"
#include "INIReader.h"
#include "INIWriter.h"


#include "BadAllocException.h"
#include "INIFileUnableToReadException.h"
#include "INIFileVariableDoesNotExistsException.h"
#include "INIFileSectionDoesNotExistException.h"

jump::system::Configuration* jump::system::Configuration::get_instance()
{
	static Configuration instance;
	return &instance;
}


jump::system::Configuration::Configuration()
{
	set_defaults();
}

jump::system::Configuration::~Configuration()
{
}

void jump::system::Configuration::set_defaults()
{
	font_path = FONT_PATH;
	
	font_names[TITLE_CODE] = TITLE_FONT_NAME;
	font_names[OPTION_CODE] = OPTIONS_FONT_NAME;
	font_names[AUTHOR_CODE] = AUTHOR_FONT_NAME;
	font_names[DEBUG_CODE] = DEBUG_FONT_NAME;

	textures_path = TEXTURES_PATH;
	xml_files = TEXTURES_XML_FILE_PATH;
	interface_path = TEXTURES_INTERFACE_TEXTURES_PATH;

	player_textures = TEXTURES_PLAYER_NAME;
	loading_textures[WHEEL_CODE] = TEXTURES_WHEEL_NAME;
	loading_textures[LOADING_BAR_CODE] = LOADING_BAR_CODE;
	items_textures = TEXTURES_ITEMS_NAME;
	hud_textures = TEXTURES_HUD_NAME;

	debug = GENERAL_DEWELOP;
	width = GENERAL_WIDTH;
	height = GENERAL_HEIGHT;
	show_fps = GENERAL_SHOW_FPS;
	start_map = GENERAL_STARTING_MAP;
	data_folder = GENERAL_DATA_FOLDER;
	max_clouds = GENERAL_MAX_CLOUDS;

	up = static_cast<sf::Keyboard::Key>(static_cast<int>(GENERAL_UP));
	down = static_cast<sf::Keyboard::Key>(static_cast<int>(GENERAL_DOWN));
	left = static_cast<sf::Keyboard::Key>(static_cast<int>(GENERAL_LEFT));
	right = static_cast<sf::Keyboard::Key>(static_cast<int>(GENERAL_RIGHT));
}


void jump::system::Configuration::load(const std::string& _file_name)
{
	try
	{
		auto ini = new ini::IniFile();

		try
		{
			auto reader = new ini::IniReader(ini, _file_name);

			ini::IniSection* section = nullptr;

#pragma region fonts
			try
			{
				section = ini->section(FONT_SECTION);

				try
				{
					font_path = section->variable(FONT_PATH_VAR_NAME)->value;
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					font_path = FONT_PATH;
				}

				try
				{
					font_names[TITLE_CODE] = section->variable(TITLE_FONT_VAR_NAME)->value;
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					font_names[TITLE_CODE] = TITLE_FONT_NAME;
				}

				try
				{
					font_names[OPTION_CODE] = section->variable(OPTIONS_FONT_VAR_NAME)->value;
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					font_names[OPTION_CODE] = OPTIONS_FONT_NAME;
				}

				try
				{
					font_names[AUTHOR_CODE] = section->variable(AUTHOR_FONT_VAR_NAME)->value;
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					font_names[AUTHOR_CODE] = AUTHOR_FONT_NAME;
				}

				try
				{
					font_names[DEBUG_CODE] = section->variable(DEBUG_FONT_VAR_NAME)->value;
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					font_names[DEBUG_CODE] = DEBUG_FONT_NAME;
				}
			}
			catch(ini::exception::IniFileSectionDoesNotExistsException)
			{
				font_path = FONT_PATH;

				font_names[TITLE_CODE] = TITLE_FONT_NAME;
				font_names[OPTION_CODE] = OPTIONS_FONT_NAME;
				font_names[AUTHOR_CODE] = AUTHOR_FONT_NAME;
				font_names[DEBUG_CODE] = DEBUG_FONT_NAME;
			}
#pragma endregion

#pragma region textures
			try
			{
				section = ini->section(TEXTURES_SECTION);

				try
				{
					textures_path = section->variable(TEXTURES_PATH_VAR_NAME)->value;
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					textures_path = TEXTURES_PATH;
				}

				try
				{
					player_textures = section->variable(TEXTURES_PLAYER_VAR_NAME)->value;
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					player_textures = TEXTURES_PLAYER_NAME;
				}

				try
				{
					xml_files = section->variable(TEXTURES_XML_FILE_PATH_VAR_NAME)->value;
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					xml_files = TEXTURES_XML_FILE_PATH;
				}

				try
				{
					interface_path = section->variable(TEXTURES_INTERFACE_TEXTURES_PATH_VAR_NAME)->value;
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					interface_path = TEXTURES_INTERFACE_TEXTURES_PATH;
				}

				try
				{
					loading_textures[WHEEL_CODE] = section->variable(TEXTURES_WHEEL_VAR_NAME)->value;
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					loading_textures[WHEEL_CODE] = TEXTURES_WHEEL_NAME;
				}

				try
				{
					loading_textures[LOADING_BAR_CODE] = section->variable(TEXTURES_LOADING_BAR_VAR_NAME)->value;
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					loading_textures[LOADING_BAR_CODE] = LOADING_BAR_CODE;
				}

				try
				{
					items_textures = section->variable(TEXTURES_ITEMS_VAR_NAME)->value;
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					items_textures = TEXTURES_ITEMS_NAME;
				}

				try
				{
					hud_textures = section->variable(TEXTURES_HUD_VAR_NAME)->value;
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					hud_textures = TEXTURES_HUD_NAME;
				}
			}
			catch (ini::exception::IniFileSectionDoesNotExistsException)
			{
				textures_path = TEXTURES_PATH;
				xml_files = TEXTURES_XML_FILE_PATH;
				interface_path = TEXTURES_INTERFACE_TEXTURES_PATH;

				player_textures = TEXTURES_PLAYER_NAME;
				loading_textures[WHEEL_CODE] = TEXTURES_WHEEL_NAME;
				loading_textures[LOADING_BAR_CODE] = LOADING_BAR_CODE;
				items_textures = TEXTURES_ITEMS_NAME;
				hud_textures = TEXTURES_HUD_NAME;
			}
#pragma endregion

#pragma region general
			try
			{
				section = ini->section(GENERAL_SECTION);

				try
				{
					debug = read_bool(section->variable(GENERAL_DEWELOP_MODE_VAR_NAME)->value, GENERAL_DEWELOP);
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					debug = GENERAL_DEWELOP;
				}

				try
				{
					width = read_int(section->variable(GENERAL_WIDHT_VAR_NAME)->value, GENERAL_WIDTH);
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					width = GENERAL_WIDTH;
				}

				try
				{
					height = read_int(section->variable(GENERAL_HEIGHT_VAR_NAME)->value, GENERAL_HEIGHT);
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					height = GENERAL_HEIGHT;
				}

				try
				{
					show_fps = read_bool(section->variable(GENERAL_FPS_SHOW_VAR_NAME)->value, GENERAL_SHOW_FPS);
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					show_fps = GENERAL_SHOW_FPS;
				}

				try
				{
					start_map = section->variable(GENERAL_STARTING_MAP_VAR_NAME)->value;
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					start_map = GENERAL_STARTING_MAP;
				}

				try
				{
					data_folder = section->variable(GENERAL_DATA_FOLDER_VAR_NAME)->value;
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					data_folder = GENERAL_DATA_FOLDER;
				}

				try
				{
					max_clouds = read_int(section->variable(GENERAL_MAX_COULDS_VAR_NAME)->value, GENERAL_MAX_CLOUDS);
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					max_clouds = GENERAL_MAX_CLOUDS;
				}

				try
				{
					up = static_cast<sf::Keyboard::Key>(static_cast<int>(read_int(section->variable(GENERAL_UP_VAR_NAME)->value, GENERAL_UP)));
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					up = static_cast<sf::Keyboard::Key>(static_cast<int>(GENERAL_UP));
				}

				try
				{
					down = static_cast<sf::Keyboard::Key>(static_cast<int>(read_int(section->variable(GENERAL_DOWN_VAR_NAME)->value, GENERAL_DOWN)));
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					down = static_cast<sf::Keyboard::Key>(static_cast<int>(GENERAL_DOWN));
				}

				try
				{
					left = static_cast<sf::Keyboard::Key>(static_cast<int>(read_int(section->variable(GENERAL_LEFT_VAR_NAME)->value, GENERAL_LEFT)));
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					left = static_cast<sf::Keyboard::Key>(static_cast<int>(GENERAL_LEFT));
				}

				try
				{
					right = static_cast<sf::Keyboard::Key>(static_cast<int>(read_int(section->variable(GENERAL_RIGHT_VAR_NAME)->value, GENERAL_RIGHT)));
				}
				catch (ini::exception::IniFileVariableDoesNotExistsException)
				{
					right = static_cast<sf::Keyboard::Key>(static_cast<int>(GENERAL_RIGHT));
				}
			}
			catch(ini::exception::IniFileSectionDoesNotExistsException)
			{
				debug = GENERAL_DEWELOP;
				width = GENERAL_WIDTH;
				height = GENERAL_HEIGHT;
				show_fps = GENERAL_SHOW_FPS;
				start_map = GENERAL_STARTING_MAP;
				data_folder = GENERAL_DATA_FOLDER;
				max_clouds = GENERAL_MAX_CLOUDS;

				up = static_cast<sf::Keyboard::Key>(static_cast<int>(GENERAL_UP));
				down = static_cast<sf::Keyboard::Key>(static_cast<int>(GENERAL_DOWN));
				left = static_cast<sf::Keyboard::Key>(static_cast<int>(GENERAL_LEFT));
				right = static_cast<sf::Keyboard::Key>(static_cast<int>(GENERAL_RIGHT));
			}
#pragma endregion

		}
		catch(ini::exception::IniFileUnableToReadException)
		{
		}
	}
	catch(std::bad_alloc)
	{
		throw exception::BadAllocException();
	}
}

void jump::system::Configuration::save(const std::string& _file_name)
{
	try
	{
		auto ini = new ini::IniFile(
		{
			new ini::IniSection(GENERAL_SECTION,
			{
				new ini::IniVariable(GENERAL_WIDHT_VAR_NAME, std::to_string(width)),
				new ini::IniVariable(GENERAL_HEIGHT_VAR_NAME, std::to_string(height)),

				new ini::IniVariable(GENERAL_STARTING_MAP_VAR_NAME, start_map),
				new ini::IniVariable(GENERAL_FPS_SHOW_VAR_NAME, std::to_string(show_fps)),
				new ini::IniVariable(GENERAL_MAX_COULDS_VAR_NAME, std::to_string(max_clouds)),

				new ini::IniVariable(GENERAL_UP_VAR_NAME, sf::String(static_cast<sf::Uint32>(up))),
				new ini::IniVariable(GENERAL_DOWN_VAR_NAME, sf::String(static_cast<sf::Uint32>(down))),
				new ini::IniVariable(GENERAL_LEFT_VAR_NAME, sf::String(static_cast<sf::Uint32>(left))),
				new ini::IniVariable(GENERAL_RIGHT_VAR_NAME, sf::String(static_cast<sf::Uint32>(right))),

				new ini::IniVariable(GENERAL_DATA_FOLDER_VAR_NAME, data_folder)

			}),
			new ini::IniSection(FONT_SECTION, 
			{
				new ini::IniVariable(FONT_PATH_VAR_NAME, font_path),
				new ini::IniVariable(TITLE_FONT_VAR_NAME, font_names[TITLE_CODE]),
				new ini::IniVariable(OPTIONS_FONT_VAR_NAME, font_names[OPTION_CODE]),
				new ini::IniVariable(AUTHOR_FONT_VAR_NAME, font_names[AUTHOR_CODE]),
				new ini::IniVariable(DEBUG_FONT_VAR_NAME, font_names[DEBUG_CODE])
			}),
			new ini::IniSection(TEXTURES_SECTION, 
			{
				new ini::IniVariable(TEXTURES_PATH_VAR_NAME, textures_path),
				new ini::IniVariable(TEXTURES_XML_FILE_PATH_VAR_NAME, xml_files),
				new ini::IniVariable(TEXTURES_INTERFACE_TEXTURES_PATH_VAR_NAME, interface_path),
				new ini::IniVariable(TEXTURES_PLAYER_VAR_NAME, player_textures),
				new ini::IniVariable(TEXTURES_WHEEL_VAR_NAME, loading_textures[WHEEL_CODE]),
				new ini::IniVariable(TEXTURES_LOADING_BAR_VAR_NAME, loading_textures[LOADING_BAR_CODE]),
				new ini::IniVariable(TEXTURES_ITEMS_VAR_NAME, items_textures),
				new ini::IniVariable(TEXTURES_HUD_VAR_NAME, hud_textures),
			})
		});

		ini::IniWriter(ini, _file_name);
	}
	catch(std::bad_alloc)
	{
		throw exception::BadAllocException();
	}
}

bool jump::system::Configuration::read_bool(const std::string& _value, const bool& _default)
{
	try
	{
		return std::stol(_value) > 0;
	}
	catch (...)
	{
		std::string value = boost::algorithm::to_upper_copy(_value);
		if (value == "TRUE")
			return true;
		else if (value== "FALSE")
			return false;
		else
			return _default;
	}
}

sf::Uint32 jump::system::Configuration::read_int(const std::string& _value, const sf::Uint32& _default)
{
	try
	{
		return std::stol(_value);
	}
	catch(...)
	{
		return _default;
	}
}
