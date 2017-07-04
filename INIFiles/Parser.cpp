#include "Parser.h"

#include <boost\algorithm/string.hpp>
#include <string>

#include "INIFileBadAllocException.h"

#include "Simbols.h"

ini::priv::Parser::Parser(std::vector<Token*>& _tokens) : tokens_(_tokens)
{
}

std::vector<ini::Section*> ini::priv::Parser::parse()
{
	std::vector<ini::Section*> result;

	bool is_section_name = false;
	bool comment = false;
	bool string = false;
	bool variable_value = false;
	std::string section_name;

	try
	{
		ini::Variable* variable = new ini::Variable();

		for (auto it = tokens_.begin(); it != tokens_.end(); ++it)
		{
			Token* token = *it;

			if (token->type == SIMBOL_NEW_LINE[0])
			{
				if (variable)
				{
					boost::algorithm::trim(variable->name);
					boost::algorithm::trim(variable->value);

					if (!variable->name.empty())
					{
						if (!result.empty())
						{
							result[result.size() - 1]->variable(variable);

							variable = new ini::Variable();
						}
						else
						{
							delete variable;
							variable = new ini::Variable();
						}
					}

					variable_value = false;
				}

				if (comment) comment = false;

				continue;
			}

			if (token->type == SIMBOL_COMMENT[0])
				comment = true;
			if (!comment)
			{
				if (token->type == SIMBOL_BEGIN_SECTION[0])
					is_section_name = true;
				else if (token->type == SIMBOL_END_SECTION[0])
				{
					is_section_name = false;

					boost::algorithm::trim(section_name);
					if (!section_name.empty())
						result.push_back(new Section(section_name));
				}
				else if (token->type == SIMBOL_STRING[0])
					string = string ? true : false;
				else if (token->type == SIMBOL_EQUAL[0])
					variable_value = true;
				else if (token->type == SIMBOL_VALUE[0])
				{
					if (string && variable_value)
						variable->value += token->value + " ";
					else if (is_section_name)
						section_name += token->value + " ";
					else
						variable->name += token->value + " ";
				}

			}
		}
	}
	catch(std::bad_alloc)
	{
		throw exception::INIFileBadAllocException();
	}

	return result;
}

