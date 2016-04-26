#include "Parser.h"

#include <codecvt>

#include <boost\algorithm\string.hpp>

using namespace mapf;
using namespace priv;

Parser::Parser(std::vector<Token*> tokens)
{
	this->tokens = tokens;
	i = 0;
}

std::wstring Parser::parseValue()
{
	int tmp = i;
	std::wstring value;

	if (i > 0 && tokens[i - 1]->op == L'=')
	{
		for (; i < tokens.size(); i++)
		{
			if (tokens[i]->op == L'"')
				i++;

			if (tokens[i]->op == L';')
				break;

			if (tokens[i]->op == L'=')
			{
				i = tmp;
				return L"";
			}

			if (tokens[i]->op == 'V')
				value += tokens[i]->value;
		}
	}

	return value;
}

auto Parser::lunch() -> std::map<std::wstring, std::wstring>
{
	std::wstring command, value;

	int number = 0;
	bool findestdot = false;

	for (; i < tokens.size(); i++)
	{
		if (tokens[i]->op == L'#')
		{
			i += 2;
		}

		if (tokens[i]->op == L'V' && tokens[i + 1]->op == L'=' && command.empty() ||
			tokens[i]->op == L'V' && tokens[i + 1]->op == L'.' && command.empty())
		{
			command = tokens[i]->value;
			if (tokens[i + 1]->op == L'.')
			{
				findestdot = true;
				command += L'.';
			}

			i++;
		}
		else if (tokens[i]->op == L'V' && tokens[i + 1]->op == L'=' && !command.empty() ||
			tokens[i]->op == L'V' && tokens[i + 1]->op == L'.' && !command.empty())
		{
			command += tokens[i]->value;
			if (tokens[i + 1]->op == L'.')
			{
				findestdot = true;
				command += L'.';
			}
			i++;
		}

		if (tokens[i]->op == L'{')
		{
			if (command.empty())
			{
				number++;
				command += std::to_wstring(number);
			}

			command += L'.';
		}

		if (tokens[i]->op == L'}')
		{
			auto pos = command.find('.');

			if (!command.empty() && 
				command[command.size() - 1] == L'.' &&
				pos != std::string::npos &&
				pos == command.size() - 1)
			{
				command.clear();
			}
			else
			{
				auto pos = command.rfind(L'.');

				if (pos == command.size() - 1)
				{
					pos = command.substr(0, pos).rfind(L'.')+1;
				}

				if (pos != std::string::npos)
				{
					command.erase(pos);
				}
			}
		}

		value = parseValue();

		if (!value.empty() && !command.empty())
		{
			std::wstring_convert <std::codecvt_utf8_utf16<wchar_t>> converter;

			map[boost::to_upper_copy(command)] = value;
			//std::cout << "Zapisuje: " << converter.to_bytes(boost::to_upper_copy(command)) << " = " << converter.to_bytes(value) << std::endl;

			auto pos = command.rfind(L'.');

			if (pos != std::string::npos)
			{
				command.erase(pos + 1, command.length() - pos);
			}

			if (findestdot)
			{
				findestdot = false;
				command.clear();
			}
		}
	}

	return map;
}

Parser::~Parser()
{
}