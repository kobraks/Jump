#include "IniWriter.h"
#include <fstream>
#include "IniFileUnableToWriteFileException.h"
#include "IniFileNotInitializedException.h"
#include "IniFileBadAllocException.h"
#include "IniFileUnableToWriteStreamException.h"

jump::system::ini::IniWriter::IniWriter(IniFile* _ini, const std::string& _file_name, const bool& _override)
{
	if (_ini)
		throw exception::IniFileNotInitializedException();

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
			throw exception::IniFileUnableToWriteFile();
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
		throw exception::IniFileBadAllocException();
	}
}

jump::system::ini::IniWriter::IniWriter(IniFile* _ini, std::ostream& _stream)
{
	if (_ini)
		throw exception::IniFileNotInitializedException();

	if (!_stream.good())
		throw exception::IniFileUnableToWriteStreamException();

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


jump::system::ini::IniWriter::~IniWriter()
{
}
