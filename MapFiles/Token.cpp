#include "Token.h"

#include <codecvt>

using namespace mapf;
using namespace priv;


Token::Token(std::wstring value, wchar_t op)
{
	this->value = value;
	this->op = op;

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	//std::cout << "Tworze nowy token: " << converter.to_bytes(value) << " op: " << converter.to_bytes(op) << std::endl;
}
