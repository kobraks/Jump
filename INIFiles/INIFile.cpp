#include "INIFile.h"
#include <algorithm>
#include "INIFileBadAllocException.h"
#include "INIFileSectionDoesNotExistException.h"
#include "INIFileSectionAlreadyExistsException.h"

ini::INIFile::INIFile()
{
}

ini::INIFile::INIFile(const std::initializer_list<Section>& _sections)
{
	section(_sections);
}

ini::INIFile::INIFile(const std::initializer_list<Section*>& _sections)
{
	section(_sections);
}

ini::INIFile::INIFile(const Section& _section)
{
	section(_section);
}

ini::INIFile::INIFile(Section* _section)
{
	section(_section);
}

ini::INIFile::INIFile(Section* _begin, Section* _end)
{
	section(_begin, _end);
}

ini::INIFile::~INIFile()
{
	clear();
}

void ini::INIFile::clear()
{
	for (auto section : sections_)
		delete section;

	sections_.clear();
}


void ini::INIFile::section(Section* _section)
{
	if (_section)
	{
		auto contains = this->find(_section->name());

		if (contains != sections_.end())
			sections_.push_back(_section);
		else
			throw exception::INIFileSectionAlreadyExistsException();
	}
}


void ini::INIFile::section(const Section& _section)
{
	try
	{
		auto section_to_add = new Section(_section);
		try
		{
			section(section_to_add);
		}
		catch(exception::INIFileSectionAlreadyExistsException)
		{
			delete section_to_add;
			throw exception::INIFileSectionAlreadyExistsException();
		}
	}
	catch (std::bad_alloc)
	{
		throw exception::INIFileBadAllocException();
	}
}

void ini::INIFile::section(const std::initializer_list<Section*>& _sections)
{
	for (auto section : _sections)
	{
		this->section(section);
	}
}

void ini::INIFile::section(const std::initializer_list<Section>& _sections)
{
	for (auto section : _sections)
	{
		this->section(section);
	}
}

void ini::INIFile::section(Section* _begin, Section* _end)
{
	for (auto i = _begin; i != _end; ++i)
		section(*i);
}

ini::Section ini::INIFile::section(const std::string& _name) const
{
	auto result = std::find_if(sections_.begin(), sections_.end(), [_name](const Section const* _section)
	{
		return _name == _section->name();
	});

	if (result != sections_.end())
		return **result;
	else
		throw exception::INIFileSectionDoesNotExistsException();
}

ini::Section* ini::INIFile::section(const std::string& _name)
{
	auto result = find(_name);

	if (result != sections_.end())
		return *result;
	else
		throw exception::INIFileSectionDoesNotExistsException();
	
}

std::vector<ini::Section*> ini::INIFile::sections() const
{
	return sections_;
}

void ini::INIFile::remove_section(const std::string& _section_name)
{
	auto section = find(_section_name);

	if (section == sections_.end())
		throw exception::INIFileSectionDoesNotExistsException();

	size_t pos = std::distance(sections_.begin(), section);
	delete sections_[pos];
	sections_.erase(sections_.begin() + pos);
}

std::vector<ini::Section*>::iterator ini::INIFile::find(const std::string& _section_name)
{
	return std::find_if(sections_.begin(), sections_.end(), 
		[_section_name](const Section const* _section)
		{
			return _section_name == _section->name();
		});
}
