#include "Tokenizer.h"

#include <boost/algorithm/string.hpp>
#include <algorithm>

#include "INIFileBadAllocException.h"

#include "Simbols.h"
#include <winerror.h>

ini::priv::Tokenizer::Tokenizer(std::vector<std::string> _lines) : lines_(_lines)
{
	
}

std::vector<ini::priv::Token*> ini::priv::Tokenizer::tokenize()
{
	std::vector<Token*> tokens;

	auto strings = split_for_tokenize(lines_);

	for (auto string : strings)
	{
		if (string == SIMBOL_NEW_LINE || 
			string == SIMBOL_COMMENT || 
			string == SIMBOL_BEGIN_SECTION || 
			string == SIMBOL_END_SECTION ||
			string == SIMBOL_EQUAL || 
			string == SIMBOL_STRING)
			tokens.push_back(new Token(string[0], ""));
		else
			tokens.push_back(new Token(SIMBOL_VALUE[0], string));
	}

	return tokens;
}

std::vector<std::string> ini::priv::Tokenizer::split_for_tokenize(std::vector<std::string> _lines) const
{
	std::vector<std::string> result;

	for (auto line : _lines)
	{
		line = prepare_for_split(line);
	}

	std::string	delimiter = " ";

	for (size_t i = 0; i < _lines.size(); ++i)
	{
		std::string line = _lines[i];

		size_t pos = 0;
		while ((pos = line.find(delimiter)) != std::string::npos)
		{
			result.push_back(line.substr(0, pos));
			line.erase(0, pos + delimiter.length());
		}
	}

	return result;
}

std::string ini::priv::Tokenizer::prepare_for_split(const std::string& _string) const
{
	std::string result = _string;
	if (result.empty())
		return result;

	std::vector<std::string> replacement = {
		"\"",
		"=",
		"[",
		"]",
		";"
	};

	for (size_t i = 0; i < replacement.size(); ++i)
	{
		result = replace(result, replacement[i], replacement[i] + " ");
	}

	result = replace(result, "  ", " ");

	if (result != "\n") boost::trim(result);

	return result;
}

std::string ini::priv::Tokenizer::replace(const std::string& _string, const std::string& _what, const std::string& _replacment) const
{
	std::string result = _string;
	size_t pos = 0;
	while((pos = result.find(_what, pos)) == std::string::npos)
	{
		result.replace(pos, _what.length(), _replacment);
		pos += _replacment.length();
	}

	return result;
}
