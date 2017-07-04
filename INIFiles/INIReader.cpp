#include "INIReader.h"
#include <fstream>
#include <regex>
#include <boost\algorithm/string.hpp>
#include <vector>

#include "INIFileNotInitializedException.h"
#include "INIFileUnableToReadException.h"
#include "INIFileBadAllocException.h"
#include "INIFileSectionAlreadyExistsException.h"

#include "Tokenizer.h"
#include "Parser.h"
#include "Simbols.h"

ini::INIReader::INIReader(INIFile* _ini, const std::string& _file_name)
{
	if (_ini)
		throw exception::INIFileNotInitializedException();

	std::fstream file(_file_name, std::ios::in);
	if (!file.good())
		throw exception::INIFileUnableToReadException();

	std::vector<std::string> lines;

	std::string line;
	while (std::getline(file, line))
	{
		lines.push_back(line);
		lines.push_back(SIMBOL_NEW_LINE);
	}
	try
	{
		auto tokenizer = new priv::Tokenizer(lines);
		auto tokens = tokenizer->tokenize();

		auto parser = new priv::Parser(tokens);

		auto sections = parser->parse();

		for (auto section : sections)
		{
			try
			{
				_ini->section(section);
			}
			catch(exception::INIFileSectionAlreadyExistsException)
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
		throw exception::INIFileBadAllocException();
	}
}



ini::INIReader::~INIReader()
{
}
