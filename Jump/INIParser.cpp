#include "IniParser.h"

#include <boost\algorithm/string.hpp>
#include <string>

#include "INIFileBadAllocException.h"
#include "Simbols.h"

jump::system::ini::IniParser::IniParser(std::vector<ini::IniToken*>& _tokens) : tokens_(_tokens), it_(tokens_.begin())
{
}

std::vector<jump::system::ini::IniSection*> jump::system::ini::IniParser::parse()
{
	std::vector<jump::system::ini::IniSection*> result;
	
	try
	{
		IniSection* section;
		while((section = get_section()))
		{
			IniVariable* variable;
			while ((variable = get_variable()))
			{
				section->variable(variable);
			}

			result.push_back(section);
		}
	}
	catch(std::bad_alloc)
	{
		throw exception::IniFileBadAllocException();
	}

	return result;
}

jump::system::ini::IniSection* jump::system::ini::IniParser::get_section()
{
	std::string section_name = "";

	for (; it_ != tokens_.end(); ++it_)
	{
		IniToken* token = *it_;
		if (token->type == SIMBOL_BEGIN_SECTION[0])
		{
			while(token->type != SIMBOL_END_SECTION[0])
			{
				if (token->type == SIMBOL_COMMENT[0])
					read_comment();
				else if (!token->value.empty())
					section_name += token->value;

				if (++it_ == tokens_.end())
					break;

				token = *it_;
			}

			if (tokens_.end() != it_)
				++it_;

			return new IniSection(section_name);

		}

	}

	return nullptr;
}

jump::system::ini::IniVariable* jump::system::ini::IniParser::get_variable()
{
	std::string var_name;
	std::string var_value;

	if (get_variable_name(var_name) && get_variable_value(var_value))
	{
		boost::algorithm::trim(var_name);
		boost::algorithm::trim(var_value);

		return new IniVariable(var_name, var_value);
	}

	return nullptr;
}

bool jump::system::ini::IniParser::get_variable_name(std::string& _var_name)
{
	for (; it_ != tokens_.end(); ++it_)
	{
		auto token = *it_;

		if (token->type == SIMBOL_COMMENT[0])
			read_comment();
		else if (token->type == SIMBOL_BEGIN_SECTION[0] ||
			token->type == SIMBOL_END_SECTION[0] ||
			token->type == SIMBOL_STRING[0])
			break;
		else if (token->type == SIMBOL_EQUAL[0])
			return true;
		else
			_var_name += token->value.empty() ? "" : token->value + " ";

	}

	return false;
}

bool jump::system::ini::IniParser::get_variable_value(std::string& _var_value)
{
	for (; it_ != tokens_.end(); ++it_)
	{
		auto token = *it_;

		if (token->type == SIMBOL_BEGIN_SECTION[0] ||
			token->type == SIMBOL_END_SECTION[0] ||
			token->type == SIMBOL_STRING[0])
			break;
		else if (token->type == SIMBOL_NEW_LINE[0] || 
			token->type == SIMBOL_COMMENT[0])
			return true;
		else
			_var_value += token->value.empty() ? "" : token->value + " ";
	}

	return false;
}

void jump::system::ini::IniParser::read_comment()
{
	for (;it_ != tokens_.end(); ++it_)
	{
		auto token = *it_;

		if (token->type == SIMBOL_NEW_LINE[0])
			return;
	}
}

