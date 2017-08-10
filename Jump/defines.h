#pragma once

#define CONFIGURATION_FILE_NAME "config.ini"
#define ENTITIES_FILE "entities.txt"
#define SFML_LOGO "sfml-logo.png"
#define BUTTON_TEXUTRE "button.png"

#define WINDOW_NAME "Jump"

#define OPTION_CODE "options"
#define AUTHOR_CODE "author"
#define TITLE_CODE "title"
#define DEBUG_CODE "debug"

#pragma region lua
#define GRAPHIC_CODE "graphic"
#define PHYSICS_CODE "physics"
#define SCRIPT_CODE "script"
#define ANIMATION_CODE "animation"
#define CONTENT_TABLE_NAME "entities"
#define IGNORE_CODE "ignore"
#pragma endregion

#define WHEEL_CODE "wheel"
#define LOADING_BAR_CODE "loadBar"

#define START_GAME "Start Game"
#define OPTIONS "Opcje"
#define EXIT "Wyjœcie"

#pragma region ini_file

#pragma region fonts

#define FONT_SECTION "fonts"

#define FONT_PATH_VAR_NAME "fonts Path"
#define TITLE_FONT_VAR_NAME "title font"
#define AUTHOR_FONT_VAR_NAME "author font"
#define DEBUG_FONT_VAR_NAME "debug font"
#define OPTIONS_FONT_VAR_NAME "options font"

#define FONT_PATH "Data/Fonts/"

#define TITLE_FONT_NAME "FRADM.ttf"
#define OPTIONS_FONT_NAME "framd.ttf"
#define AUTHOR_FONT_NAME "FRADM.ttf"
#define DEBUG_FONT_NAME "consola.ttf"

#pragma endregion

#pragma region textures
#define TEXTURES_SECTION "textures"

#define TEXTURES_PATH_VAR_NAME "textures Path"
#define TEXTURES_PLAYER_VAR_NAME "player textures"
#define TEXTURES_XML_FILE_PATH_VAR_NAME "path to xml files"
#define TEXTURES_INTERFACE_TEXTURES_PATH_VAR_NAME "interface textures path"
#define TEXTURES_WHEEL_VAR_NAME "loading wheel"
#define TEXTURES_LOADING_BAR_VAR_NAME "loading bar"
#define TEXTURES_ITEMS_VAR_NAME "items"
#define TEXTURES_HUD_VAR_NAME "hud"

#define TEXTURES_PATH "Data/Textures/"
#define TEXTURES_XML_FILE_PATH "Data/XML/"
#define TEXTURES_INTERFACE_TEXTURES_PATH "Data/Interface/"

#define TEXTURES_PLAYER_NAME "Player.png"
#define TEXTURES_WHEEL_NAME "wheel.png"
#define TEXTURES_LOADING_BAR_NAME "loadbar.png"
#define TEXTURES_ITEMS_NAME "items.png"
#define TEXTURES_HUD_NAME "hud.png"

#pragma endregion

#pragma region general

#define GENERAL_SECTION "general"

#define GENERAL_DEWELOP_MODE_VAR_NAME "dewelop mode"
#define GENERAL_WIDHT_VAR_NAME "width"
#define GENERAL_HEIGHT_VAR_NAME "height"
#define GENERAL_STARTING_MAP_VAR_NAME "starting map"
#define GENERAL_FPS_SHOW_VAR_NAME "show fps"
#define GENERAL_DATA_FOLDER_VAR_NAME "data folder"
#define GENERAL_MAX_COULDS_VAR_NAME "max clouds"

#define GENERAL_UP_VAR_NAME "Up"
#define GENERAL_DOWN_VAR_NAME "Down"
#define GENERAL_LEFT_VAR_NAME "Left"
#define GENERAL_RIGHT_VAR_NAME "Right"

#define GENERAL_DEWELOP true
#define GENERAL_WIDTH 800
#define GENERAL_HEIGHT 600
#define GENERAL_STARTING_MAP "example.txt"
#define GENERAL_SHOW_FPS true
#define GENERAL_DATA_FOLDER "Data"
#define GENERAL_MAX_CLOUDS 5

#define GENERAL_UP 22
#define GENERAL_DOWN 18
#define GENERAL_LEFT 0
#define GENERAL_RIGHT 3

#pragma endregion

#pragma endregion