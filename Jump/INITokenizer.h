#pragma once
#include <vector>
#include <string>
#include "IniToken.h"

namespace jump
{
	namespace system
	{
		namespace ini
		{
			class IniTokenizer
			{
			public:
				IniTokenizer(std::vector<std::string> _lines);

				std::vector<IniToken*> tokenize();

			private:
				std::vector<std::string> lines_;

				std::vector<std::string> split_for_tokenize(std::vector<std::string> _lines) const;
				std::string prepare_for_split(const std::string& _string) const;

				static std::string replace(const std::string& _string, const std::string& _what, const std::string& _replacment);
			};
		}
	}
}