#include "IniSection.h"
#include <algorithm>
#include <boost/algorithm/string.hpp>

#include "IniFileBadAllocException.h"
#include "IniFileVariableDoesNotExistsException.h"

jump::system::ini::IniSection::IniSection(const std::string& _name) : name_(_name)
{}

jump::system::ini::IniSection::IniSection(const std::string& _name, const std::initializer_list<IniVariable*>& _variables) : IniSection(_name)
{
	variable(_variables);
}

jump::system::ini::IniSection::IniSection(const std::string& _name, const std::initializer_list<IniVariable>& _variables) : IniSection(_name)
{
	variable(_variables);
}

jump::system::ini::IniSection::IniSection(const std::string& _name, const IniVariable _variable) : IniSection(_name)
{
	variable(_variable);
}

jump::system::ini::IniSection::IniSection(const std::string& _name, IniVariable* _variable) : IniSection(_name)
{
	variable(_variable);
}

jump::system::ini::IniSection::IniSection(const std::string& _name, IniVariable* _begin, IniVariable* _end) : IniSection(_name)
{
	variable(_begin, _end);
}

jump::system::ini::IniSection::IniSection(const IniSection& _section)
{
	try
	{
		for (auto variable : _section.variables_)
			variables_.push_back(new IniVariable(*variable));

		name_ = _section.name();
	}
	catch(std::bad_alloc)
	{
		throw exception::IniFileBadAllocException();
	}
}

jump::system::ini::IniSection::~IniSection()
{
	clear();
}

void jump::system::ini::IniSection::clear()
{
	for (auto variable : variables_)
		delete variable;

	variables_.clear();
}

void jump::system::ini::IniSection::name(const std::string& _name)
{
	if (_name != "" || !_name.empty())
		name_ = _name;
}

std::string jump::system::ini::IniSection::name() const
{
	return name_;
}

jump::system::ini::IniVariable jump::system::ini::IniSection::variable(const std::string& _var_name) const
{
	auto result = std::find_if(variables_.begin(), variables_.end(), 
		[_var_name](const IniVariable* const _variable)
	{
		return boost::algorithm::to_upper_copy(_var_name) == boost::algorithm::to_upper_copy(_variable->name);
	});

	if (result != variables_.end())
		return **result;
	else
		throw exception::IniFileVariableDoesNotExistsException();
}

jump::system::ini::IniVariable* jump::system::ini::IniSection::variable(const std::string& _variable)
{
	auto result = find(_variable);

	if (result != variables_.end())
		return *result;
	else
		throw exception::IniFileVariableDoesNotExistsException();
}


void jump::system::ini::IniSection::variable(IniVariable* _variable)
{
	if (_variable)
	{
		auto var = find(_variable->name);

		if (var != variables_.end())
		{
			size_t pos = std::distance(variables_.begin(), var);
			delete variables_[pos];
			variables_[pos] = _variable;
		}
		else
			variables_.push_back(_variable);
	}
}

void jump::system::ini::IniSection::variable(const IniVariable& _variable)
{
	try
	{
		auto var = find(_variable.name);

		if (var != variables_.end())
		{
			size_t pos = std::distance(variables_.begin(), var);
			variables_[pos]->value = _variable.value;
		}
		else
			variables_.push_back(new IniVariable(_variable));
	}
	catch(std::bad_alloc)
	{
		throw exception::IniFileBadAllocException();
	}
}

std::vector<jump::system::ini::IniVariable*> jump::system::ini::IniSection::variables() const
{
	return variables_;
}

void jump::system::ini::IniSection::variable(IniVariable* _begin, IniVariable* _end)
{
	for (auto i = _begin; i != _end; ++i)
		variable(*i);
}

void jump::system::ini::IniSection::variable(const std::initializer_list<IniVariable>& _variables)
{
	for (auto variable : _variables)
		this->variable(variable);
}

void jump::system::ini::IniSection::variable(const std::initializer_list<IniVariable*>& _variables)
{
	for (auto variable : _variables)
		this->variable(variable);
}

std::vector<jump::system::ini::IniVariable*>::iterator jump::system::ini::IniSection::find(const std::string& _var_name)
{
	return std::find_if(variables_.begin(), variables_.end(), 
		[_var_name](const IniVariable* const _variable)
	{
		return boost::algorithm::to_upper_copy(_var_name) == boost::algorithm::to_upper_copy(_variable->name);
	});
}

void jump::system::ini::IniSection::remove_variable(const std::string& _variable_name)
{
	auto variable = find(_variable_name);

	if (variable == variables_.end())
		throw exception::IniFileVariableDoesNotExistsException();

	size_t pos = std::distance(variables_.begin(), variable);
	delete variables_[pos];
	variables_.erase(variables_.begin() + pos);
}
