#include "MapFiles.h"

#include <fstream>
#include <locale>
#include <codecvt>

#include <boost\algorithm\string.hpp>

#include "Token.h"
#include "Tokenizer.h"
#include "Parser.h"

using namespace mapf;

std::wstring stows(std::string s)
{
	std::wstring temp;
	temp.assign(s.begin(), s.end());
	return temp;
}

std::string wstos(std::wstring ws)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
	
	return convert.to_bytes(ws);
}

bool find(std::map <std::wstring, std::wstring>& map, std::wstring what)
{
	for (auto element : map)
	{
		auto pos = element.first.find(what + L'.');
		if (pos != std::string::npos)
		{
			return true;
		}
	}

	return false;
}

MapFiles::MapFiles()
{
	name = L"";
	isGood = false;
}

MapFiles::MapFiles(std::string name)
{
	isGood = false;
	open(name);
}

MapFiles::MapFiles(std::wstring name)
{
	isGood = false;
	open(name);
}

MapFiles::MapFiles(const char* name)
{
	isGood = false;
	open(name);
}

MapFiles::MapFiles(const wchar_t* name)
{
	isGood = false;
	open(name);
}

void MapFiles::open(std::string name)
{
	this->name.assign(name.begin(), name.end());
	open();
}

void MapFiles::open(std::wstring name)
{
	this->name = name;
	open();
}

void MapFiles::open(const char* name)
{
	std::string temp = name;
	this->name.assign(temp.begin(), temp.end());
	open();
}

void MapFiles::open(const wchar_t* name)
{
	this->name;
	open();
}

MapFiles::~MapFiles()
{
	close();
}

void MapFiles::open()
{
	std::wifstream file(name);
	this->isGood = file.good();

	if (isGood)
	{
		std::locale local(std::locale(), new std::codecvt_utf8<wchar_t>);
		file.imbue(local);

		std::wstring buff;

		priv::Tokenizer* tokenizer;
		std::vector<priv::Token*> tokens;

		priv::Parser* parser;

		while (std::getline(file, buff))
		{
			auto pos = buff.find('#');

			if (pos != std::string::npos) buff = buff.erase(pos);

			if (!buff.empty())
			{
				tokenizer = new priv::Tokenizer(buff);
				tokenizer->tokenize(tokens);

				delete tokenizer;
			}
		}

		parser = new priv::Parser(tokens);
		values = parser->lunch();

		delete parser;

		for (int i = 0; i < tokens.size(); i++)
		{
			delete tokens[i];
		}
		tokens.clear();
	}

	file.close();
}

void MapFiles::close()
{
	this->values.clear();
}

bool MapFiles::good()
{
	return isGood;
}

bool MapFiles::exist(std::wstring what)
{
	boost::to_upper(what);
	if (values.empty()) return false;

	if (values.find(what) == values.end())
		return false;
	else
		return true;
}

bool MapFiles::exist(std::string what)
{
	return exist(stows(what));
}

std::wstring MapFiles::getValue(std::wstring command)
{
	if (exist(boost::to_upper_copy(command)))
		return values[boost::to_upper_copy(command)];
	else
		return L"";
}

std::string MapFiles::getValue(std::string command)
{
	if (exist(boost::to_upper_copy(stows(command))))
		return wstos(values[boost::to_upper_copy(stows(command))]);
	else
		return "";
}

std::wstring MapFiles::operator[](std::wstring command)
{
	return this->getValue(command);
}

std::string MapFiles::operator[](std::string command)
{
	return this->getValue(command);
}

int MapFiles::getSize()
{
	int size = 0;

	for (int i = 0; i < values.size(); i++)
	{
		if (find(this->values, std::to_wstring(i))) size++;
	}

	return size;
}

bool MapFiles::getBool(std::wstring command)
{
	std::wstring value = this->operator[](command);

	if (value.empty()) return false;

	if (boost::to_lower_copy(value) == L"true") return true;
	else if (boost::to_lower_copy(value) == L"false") return false;
	else return false;
}

bool MapFiles::getBool(std::string command)
{
	return getBool(stows(command));
}

unsigned int MapFiles::getUInt(std::wstring command)
{
	std::wstring value = this->operator[](command);

	if (value.empty()) return 0;
	else return std::stoul(value);
}

unsigned int MapFiles::getUInt(std::string command)
{
	return getUInt(stows(command));
}

int MapFiles::getInt(std::wstring command)
{
	std::wstring value = this->operator[](command);

	if (value.empty()) return 0;
	else return std::stoi(value);
}

int MapFiles::getInt(std::string command)
{
	return getInt(stows(command));
}

float MapFiles::getFloat(std::wstring command)
{
	std::wstring value = this->operator[](command);

	if (value.empty()) return 0;
	else
	{
		std::replace(value .begin(), value.end(), L',', L'.');
		return std::stof(value);
	}
}

float MapFiles::getFloat(std::string command)
{
	return getFloat(stows(command));
}