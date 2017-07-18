#include "IniReader.h"
#include <fstream>
#include <regex>
#include <boost\algorithm/string.hpp>
#include <vector>

#include "IniFileNotInitializedException.h"
#include "IniFileUnableToReadException.h"
#include "IniFileBadAllocException.h"
#include "IniFileSectionAlreadyExistsException.h"

#include "IniTokenizer.h"
#include "IniParser.h"
#include "Simbols.h"

jump::system::ini::IniReader::IniReader(jump::system::ini::IniFile* _ini, const std::string& _file_name)
{
	if (_ini)
		throw exception::IniFileNotInitializedException();

	std::fstream file(_file_name, std::ios::in);
	if (!file.good())
		throw exception::IniFileUnableToReadException();

	std::vector<std::string> lines;

	std::string line;
	while (std::getline(file, line))
	{
		lines.push_back(line);
		lines.push_back(SIMBOL_NEW_LINE);
	}
	try
	{
		auto tokenizer = new IniTokenizer(lines);
		auto tokens = tokenizer->tokenize();

		auto parser = new IniParser(tokens);

		auto sections = parser->parse();

		for (auto section : sections)
		{
			try
			{
				_ini->section(section);
			}
			catch(exception::IniFileSectionAlreadyExistsException)
			{
				auto section_ini = _ini->section(section->name());
				
				for (auto variable : section_ini->variables())
					section->variable(variable);

				delete section;
			}

		}

		delete tokenizer;
		delete parser;

		for (auto token : tokens)
		{
			delete token;
		}
		tokens.clear();
	}
	catch(std::bad_alloc)
	{
		throw exception::IniFileBadAllocException();
	}
}



jump::system::ini::IniReader::~IniReader()
{
}
