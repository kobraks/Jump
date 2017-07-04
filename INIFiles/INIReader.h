#pragma once
#include <string>
#include <istream>

#include "Exports.hpp"
#include "INIFile.h"

namespace ini
{
	class INIFILES INIReader
	{
	public:
		INIReader(INIFile* _ini, const std::string& _file_name);
		INIReader(INIFile* _ini, std::istream& _input);

		~INIReader();
	};
}

