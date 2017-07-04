#pragma once
#include <string>
#include <ostream>

#include "Exports.hpp"
#include "INIFile.h"

namespace ini
{
	class INIFILES INIWriter
	{
	public:
		INIWriter(INIFile* _ini, const std::string& _file_name, const bool& _override = true);
		INIWriter(INIFile* _ini, std::ostream& _stream);
		~INIWriter();
	};
}
