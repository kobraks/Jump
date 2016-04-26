#include "Variable.hpp"
#include <regex>
#include <boost\algorithm\string.hpp>

using namespace ini;

Variable::Variable()
{
}

Variable::Variable(std::wstring name, std::wstring value)
{
	this->name = name;
	this->var = value;
}

Variable::Variable(std::wstring line)
{
	std::wregex pattern(L"=");
	std::wsmatch wynik;

	if (std::regex_search(line, wynik, pattern))
	{
		//Je¿eli znaleziono wzór to sprawdŸ czy nie ma komentarza przed =
		bool find = false;					//Czy znaleziono ju¿ = 
		std::wstring name;				//Zaiwera nazwê
		std::wstring value;				//Zawiera wartoœæ

		for (int i = 0; i < line.length(); i++)
		{
			if (line.at(i) != L'=')
			{
				if (!find) name += line.at(i);
				else value += line.at(i);
			}
			else if (line.at(i) == L'=')	find = true;
		}

		boost::algorithm::trim(name);				//Usuwanie spacji z koñca i pocz¹tku nazwy
		boost::algorithm::trim(value);				//Usuwanie spacji z koñca i pocz¹tku wartoœci

		this->name = name;							//Ustawienie nazwy zmiennej
		this->var = value;								//Ustawienie wartoœci zmiennej
	}
	else this->name = line;
}

//-------------------------------------------------------------Komentarze zmiennych-------------------------------------------------

void Variable::addComment(std::wstring comment)
{
	this->comments.push_back(std::shared_ptr<std::wstring>(new std::wstring(comment)));
}

void Variable::deleteAllComments()
{
	comments.clear();
}

void Variable::deleteComment(int line)
{
	if (comments.empty()) return;
	else if (line > comments.size()) return;
	else if (line < 0) return;
	else comments.erase(comments.begin() + line);
}

std::wstring Variable::getComment(int line)
{
	if (comments.empty()) return L"";
	else if (line < 0) return L"";
	else if (line > this->comments.size()) return L"";
	else return *this->comments.at(line);
}

auto Variable::getComments() -> std::vector <std::wstring>
{
	std::vector <std::wstring> buff(this->comments.size());

	for (int i = 0; i < this->comments.size(); i++)
		buff[i] = *comments[i];

	return buff;
}

//-------------------------------------------Wartoœci---------------------------------------
void Variable::setValue(std::wstring value)
{
	this->var = value;
}

std::wstring Variable::getValue()
{
	return this->var;
}

//-------------------------------------------Nazwa-------------------------------------------

void Variable::setName(std::wstring name)
{
	this->name = name;
}

std::wstring Variable::getName()
{
	return this->name;
}

std::wstring Variable::getLine()
{
	return this->name + L" = " + this->var;
}

Variable::~Variable()
{
	comments.clear();
}
