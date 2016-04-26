#pragma once

#include <string>
#include <vector>
#include <cctype>

#include "Token.h"

namespace mapf
{
	namespace priv
	{
		class Tokenizer
		{
		public:
			Tokenizer(std::wstring input);
			~Tokenizer();

			void tokenize(std::vector<Token*>& tokens);
		private:
			std::wstring input;
			std::wstring temp;
		};
	}
}
