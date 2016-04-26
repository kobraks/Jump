#include "Tokenizer.h"

#include <boost\algorithm\string.hpp>

using namespace mapf;
using namespace priv;


Tokenizer::Tokenizer(std::wstring input)
{
	this->input = input;
}


Tokenizer::~Tokenizer()
{
}

void Tokenizer::tokenize(std::vector<Token*>& tokens)
{
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] != L'{' &&
			input[i] != L'}' &&
			input[i] != L'=' &&
			input[i] != L'"' &&
			input[i] != L';' &&
			input[i] != L'.')
		{
			while (input[i] != L'{' &&
				input[i] != L'}'&&
				input[i] != L'='&&
				input[i] != L'"' &&
				input[i] != L';' &&
				input[i] != L',')
			{
				temp += input[i];
				if (i < input.size()) i++;
				else break;
			}

			boost::trim(temp);
			if (!temp.empty() && temp != L"" && temp != L"\t")
				tokens.push_back(new Token(temp, L'V'));

			temp.clear();
		}

		if (input[i] == L'{' ||
			input[i] == L'}' ||
			input[i] == L'=' ||
			input[i] == L';' ||
			input[i] == L'"' ||
			input[i] == L'.')
		{
			temp += input[i];

			tokens.push_back(new Token(L"", temp[0]));
			temp.clear();
		}
	}
}