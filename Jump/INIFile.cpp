#include "IniFile.h"

#include <algorithm>

#include "IniFileBadAllocException.h"
#include "IniFileSectionDoesNotExistException.h"
#include "IniFileSectionAlreadyExistsException.h"
#include <boost/algorithm/string.hpp>

jump::system::ini::IniFile::IniFile()
{
}

jump::system::ini::IniFile::IniFile(const std::initializer_list<IniSection>& _sections)
{
	section(_sections);
}

jump::system::ini::IniFile::IniFile(const std::initializer_list<IniSection*>& _sections)
{
	section(_sections);
}

jump::system::ini::IniFile::IniFile(const IniSection& _section)
{
	section(_section);
}

jump::system::ini::IniFile::IniFile(IniSection* _section)
{
	section(_section);
}

jump::system::ini::IniFile::IniFile(IniSection* _begin, IniSection* _end)
{
	section(_begin, _end);
}

jump::system::ini::IniFile::~IniFile()
{
	clear();
}

void jump::system::ini::IniFile::clear()
{
	for (auto section : sections_)
		delete section;

	sections_.clear();
}


void jump::system::ini::IniFile::section(IniSection* _section)
{
	if (_section)
	{
		auto contains = this->find(_section->name());

		if (contains == sections_.end())
			sections_.push_back(_section);
		else
			throw exception::IniFileSectionAlreadyExistsException();
	}
}


void jump::system::ini::IniFile::section(const IniSection& _section)
{
	try
	{
		auto section_to_add = new IniSection(_section);
		try
		{
			section(section_to_add);
		}
		catch(exception::IniFileSectionAlreadyExistsException)
		{
			delete section_to_add;
			throw exception::IniFileSectionAlreadyExistsException();
		}
	}
	catch (std::bad_alloc)
	{
		throw exception::IniFileBadAllocException();
	}
}

void jump::system::ini::IniFile::section(const std::initializer_list<IniSection*>& _sections)
{
	for (auto section : _sections)
	{
		this->section(section);
	}
}

void jump::system::ini::IniFile::section(const std::initializer_list<IniSection>& _sections)
{
	for (auto section : _sections)
	{
		this->section(section);
	}
}

void jump::system::ini::IniFile::section(IniSection* _begin, IniSection* _end)
{
	for (auto i = _begin; i != _end; ++i)
		section(*i);
}

jump::system::ini::IniSection jump::system::ini::IniFile::section(const std::string& _name) const
{
	auto result = std::find_if(sections_.begin(), sections_.end(), [_name](const IniSection* const _section)
	{
		return boost::algorithm::to_upper_copy(_name) == boost::algorithm::to_upper_copy(_section->name());
	});

	if (result != sections_.end())
		return **result;
	else
		throw exception::IniFileSectionDoesNotExistsException();
}

jump::system::ini::IniSection* jump::system::ini::IniFile::section(const std::string& _name)
{
	auto result = find(_name);

	if (result != sections_.end())
		return *result;
	else
		throw exception::IniFileSectionDoesNotExistsException();
	
}

std::vector<jump::system::ini::IniSection*> jump::system::ini::IniFile::sections() const
{
	return sections_;
}

void jump::system::ini::IniFile::remove_section(const std::string& _section_name)
{
	auto section = find(_section_name);

	if (section == sections_.end())
		throw exception::IniFileSectionDoesNotExistsException();

	size_t pos = std::distance(sections_.begin(), section);
	delete sections_[pos];
	sections_.erase(sections_.begin() + pos);
}

std::vector<jump::system::ini::IniSection*>::iterator jump::system::ini::IniFile::find(const std::string& _section_name)
{
	return std::find_if(sections_.begin(), sections_.end(), 
		[_section_name](const IniSection* const _section)
		{
			return boost::algorithm::to_upper_copy(_section_name) == boost::algorithm::to_upper_copy(_section->name());
		});
}
