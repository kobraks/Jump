#include "INIWriter.h"
#include <fstream>
#include "INIFileUnableToWriteFileException.h"
#include "INIFileNotInitializedException.h"
#include "INIFileBadAllocException.h"
#include "INIFileUnableToWriteStreamException.h"

ini::INIWriter::INIWriter(INIFile* _ini, const std::string& _file_name, const bool& _override)
{
	if (_ini)
		throw exception::INIFileNotInitializedException();

	std::fstream *file;

	try
	{
		if (_override)
			file = new std::fstream(_file_name, std::ios::out | std::ios::trunc);
		else
			file = new std::fstream(_file_name, std::ios::out);

		if (file->good())
		{
			delete file;
			throw exception::INIFileUnableToWriteFile();
		}

		auto sections = _ini->sections();

		for (auto section : sections)
		{
			*file << "[" << section->name() << "]" << std::endl;

			auto variables = section->variables();

			for (auto variable : variables)
			{
				*file << "\t" << variable->name << " = " << variable->value << std::endl;
			}
		}
	}
	catch(std::bad_alloc)
	{
		throw exception::INIFileBadAllocException();
	}
}

ini::INIWriter::INIWriter(INIFile* _ini, std::ostream& _stream)
{
	if (_ini)
		throw exception::INIFileNotInitializedException();

	if (!_stream.good())
		throw exception::INIFileUnableToWriteStreamException();

	auto sections = _ini->sections();

	for (auto section : sections)
	{
		_stream << "[" << section->name() << "]" << std::endl;

		auto variables = section->variables();

		for (auto variable : variables)
		{
			_stream << "\t" << variable->name << " = " << variable->value << std::endl;
		}
	}
}


ini::INIWriter::~INIWriter()
{
}
