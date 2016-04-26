#pragma once

#include <string>
#include <vector>
#include <map>

#include "exports.h"

namespace mapf
{
	class MapFiles
	{
	public:
		MAPF_MAPFILE MapFiles();
		MAPF_MAPFILE MapFiles(std::string name);
		MAPF_MAPFILE MapFiles(std::wstring name);
		MAPF_MAPFILE MapFiles(const char* name);
		MAPF_MAPFILE MapFiles(const wchar_t* name);

		MAPF_MAPFILE ~MapFiles();

		MAPF_MAPFILE void open(std::wstring name);
		MAPF_MAPFILE void open(std::string name);
		MAPF_MAPFILE void open(const char* name);
		MAPF_MAPFILE void open(const wchar_t* name);

		MAPF_MAPFILE bool good();

		MAPF_MAPFILE void close();

		MAPF_MAPFILE std::wstring getValue(std::wstring command);
		MAPF_MAPFILE std::string getValue(std::string command);

		MAPF_MAPFILE std::wstring operator[](std::wstring command);
		MAPF_MAPFILE std::string operator[](std::string command);

		MAPF_MAPFILE int getSize();

		MAPF_MAPFILE bool getBool(std::wstring command);
		MAPF_MAPFILE bool getBool(std::string command);
		MAPF_MAPFILE unsigned int getUInt(std::wstring command);
		MAPF_MAPFILE unsigned int getUInt(std::string command);
		MAPF_MAPFILE int getInt(std::wstring command);
		MAPF_MAPFILE int getInt(std::string command);
		MAPF_MAPFILE float getFloat(std::wstring command);
		MAPF_MAPFILE float getFloat(std::string command);

		MAPF_MAPFILE bool exist(std::wstring command);
		MAPF_MAPFILE bool exist(std::string command);
	private:
		std::wstring name;
		
		std::map<std::wstring, std::wstring> values;
		bool isGood;

		void open();
	};
}