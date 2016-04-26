#pragma once
#include <ostream>
#include <string>
#include <vector>
#include <memory>
#include "Section.hpp"
#include "Exports.hpp"

namespace ini
{
	class INIFiles
	{
	public:
		INI_INIFILES INIFiles();
		INI_INIFILES INIFiles(std::wstring name);
		INI_INIFILES INIFiles(std::string name);
		virtual INI_INIFILES  ~INIFiles();

		INI_INIFILES void open(std::wstring name);								//Wczytanie pliku do pamiêci
		INI_INIFILES void open(std::string name);								//Wczytanie pliku do pamiêci
		INI_INIFILES void close();															//Zamkniêcie pliku
		INI_INIFILES void save();															//Zapis pliku
		INI_INIFILES void save(std::wstring name);								//Zapis jako
		INI_INIFILES void save(std::string name);									//Zapis jako

		INI_INIFILES void setPrecision(int precision);							//Ustawienie precyzji zmiennych przecinkowych
		INI_INIFILES int getPrecision();													//Pobranie precyzji

		INI_INIFILES bool isOpened();													//Czy plik zosta³ otwarty

																			//zapisywanie wartoœci do pliku
		INI_INIFILES void write(std::wstring section, std::wstring value_name, std::wstring value);
		INI_INIFILES void write(std::wstring section, std::wstring value_name, std::string value);
		INI_INIFILES void write(std::wstring section, std::wstring value_name, wchar_t value);
		INI_INIFILES void write(std::wstring section, std::wstring value_name, const wchar_t* value);
		INI_INIFILES void write(std::wstring section, std::wstring value_name, char value);
		INI_INIFILES void write(std::wstring section, std::wstring value_name, const char* value);
		INI_INIFILES void write(std::wstring section, std::wstring value_name, int value);
		INI_INIFILES void write(std::wstring section, std::wstring value_name, float value);
		INI_INIFILES void write(std::wstring section, std::wstring value_name, double value);
		INI_INIFILES void write(std::wstring section, std::wstring value_name, bool value);
		
		INI_INIFILES void write(std::string section, std::string value_name, std::wstring value);
		INI_INIFILES void write(std::string section, std::string value_name, std::string value);
		INI_INIFILES void write(std::string section, std::string value_name, wchar_t value);
		INI_INIFILES void write(std::string section, std::string value_name, const wchar_t* value);
		INI_INIFILES void write(std::string section, std::string value_name, char value);
		INI_INIFILES void write(std::string section, std::string value_name, const char* value);
		INI_INIFILES void write(std::string section, std::string value_name, int value);
		INI_INIFILES void write(std::string section, std::string value_name, float value);
		INI_INIFILES void write(std::string section, std::string value_name, double value);
		INI_INIFILES void write(std::string section, std::string value_name, bool value);

		//odczytywanie wartoœci z pliku
		INI_INIFILES std::wstring read(std::wstring section, std::wstring value_name, std::wstring default_value);
		INI_INIFILES std::string read(std::wstring section, std::wstring value_name, std::string default_value);
		INI_INIFILES wchar_t read(std::wstring section, std::wstring value_name, wchar_t default_value);
		INI_INIFILES const wchar_t* read(std::wstring section, std::wstring value_name, const wchar_t* default_value);
		INI_INIFILES char read(std::wstring section, std::wstring value_name, char default_value);
		INI_INIFILES const char* read(std::wstring section, std::wstring value_name, const char* default_value);
		INI_INIFILES int read(std::wstring section, std::wstring value_name, int default_value);
		INI_INIFILES float read(std::wstring section, std::wstring value_name, float default_value);
		INI_INIFILES double read(std::wstring section, std::wstring value_name, double default_value);
		INI_INIFILES bool read(std::wstring section, std::wstring value_name, bool default_value);

		INI_INIFILES std::wstring read(std::string section, std::string value_name, std::wstring default_value);
		INI_INIFILES std::string read(std::string section, std::string value_name, std::string default_value);
		INI_INIFILES wchar_t read(std::string section, std::string value_name, wchar_t default_value);
		INI_INIFILES const wchar_t* read(std::string section, std::string value_name, const wchar_t* default_value);
		INI_INIFILES char read(std::string section, std::string value_name, char default_value);
		INI_INIFILES const char* read(std::string section, std::string value_name, const char* default_value);
		INI_INIFILES int read(std::string section, std::string value_name, int default_value);
		INI_INIFILES float read(std::string section, std::string value_name, float default_value);
		INI_INIFILES double read(std::string section, std::string value_name, double default_value);
		INI_INIFILES bool read(std::string section, std::string value_name, bool default_value);

	private:
		int precision;																							//Precyzja zmiennych przecinkowych
		std::wstring name;																				//Nazwa pliku
		std::vector<std::shared_ptr<Section>> sections;								//Poszeczegulne sekcje pliku ini
		std::vector<std::shared_ptr<std::wstring>> comments;					//komentarze pliku ini
		bool _isOpened;																					//Przechowuje informacje czy plik jest otwarty

		void deleteDuplicate();																			//Usuwa duplikaty
		void open();																							//Otwarcie pliku
		std::shared_ptr<Section> findSection(std::wstring name);					//Zwraca adres do sekcji jeœli takow¹ znaleziono
	};
}

