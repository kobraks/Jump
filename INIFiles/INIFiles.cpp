#include "INIFiles.hpp"

#include <cmath>
#include <fstream>
#include <Windows.h>
#include <boost/algorithm/string.hpp>

#include <locale>
#include <codecvt>

using namespace ini;

INIFiles::INIFiles()
{
	_isOpened = false;
	precision = 3;
}

INIFiles::INIFiles(std::wstring name)
{
	precision = 3;

	open(name);
}

INIFiles::INIFiles(std::string name)
{
	precision = 3;

	open(name);
}

INIFiles::~INIFiles()
{
	precision = 0;

	close();
}

void INIFiles::close()
{
	name = L"";
	sections.clear();
}

void INIFiles::open(std::wstring name)
{
	this->name = name;

	open();
}

void INIFiles::open(std::string name)
{
	this->name.assign(name.begin(), name.end());

	open();
}

void INIFiles::open()
{
	int numberOfSections = Section::getNumberOfSectionsInFile(name);

	std::wfstream *file = new std::wfstream(name, std::ios::in);
	_isOpened = file->good();

	std::locale local(std::locale(), new std::codecvt_utf8<wchar_t>);
	file->imbue(local);

	if (file->good())
	{
		std::wstring line;
		int pos = file->tellg();

		while (std::getline(*file, line))
		{
			int npos = file->tellg();

			if (Section::isSectionName(line)) break;
			else if (line[0] == L';') comments.push_back(std::shared_ptr<std::wstring>(new std::wstring(line)));
		}
		file->seekg(pos);

		while (!file->eof() && sections.size() != numberOfSections)
		{

			sections.push_back(std::shared_ptr<Section>(new Section()));
			*file >> *sections[sections.size() - 1];
		}

		for (int i = 0; i < sections.size(); i++)
		{
			if (sections[i]->getName().empty()) sections.erase(sections.begin() + i);
		}

		this->deleteDuplicate();
	}
	file->close();
	delete file;
}

void INIFiles::save()
{
	save(name);
}

void INIFiles::save(std::string name)
{
	std::wstring temp;
	temp.assign(name.begin(), name.end());
	save(temp);
}

void INIFiles::save(std::wstring name)
{
	if (!sections.empty() && name != L"")
	{
		std::wfstream* file = new std::wfstream(name, std::ios::out);
		_isOpened = file->good();

		std::locale local(std::locale(), new std::codecvt_utf8<wchar_t>);
		file->imbue(local);

		if (file->good())
		{
			for (auto element : this->comments) *file << *element << std::endl;

			for (int i = 0; i < sections.size(); i++)
			{
				*file << *sections[i];
				if (i != sections.size() - 1) *file << std::endl;
			}
		}

		file->close();
		delete file;
	}
}

void INIFiles::setPrecision(int precision)
{
	this->precision = precision;
}

int INIFiles::getPrecision()
{
	return this->precision;
}

bool INIFiles::isOpened()
{
	return _isOpened;
}

auto INIFiles::findSection(std::wstring name) -> std::shared_ptr<Section>
{
	std::shared_ptr<Section> section = NULL;

	for (auto element : sections)
	{
		if (boost::to_upper_copy(element->getName()) == boost::to_upper_copy(name)) return element;
	}
	return section;
}

void INIFiles::deleteDuplicate()
{
	for (int i = 0; i < sections.size(); i++)
	{
		for (int b = 0; b < sections.size(); b++)
		{
			if (b != i && sections[i]->getName() == sections[b]->getName() && b > i)
			{
				sections.erase(sections.begin() + i);
			}
		}
	}
}

/*--------------------------------------------------------------------Write------------------------------------------------------------*/
void INIFiles::write(std::wstring section, std::wstring valueName, std::wstring value)
{
	if (sections.empty()) sections.push_back(std::shared_ptr<Section>(new Section(section, valueName, value)));
	else
	{
		auto sectionInFile = findSection(section);

		if (sectionInFile != NULL)
		{
			sectionInFile->addValue(valueName, value);
			save();
			return;
		}

		sections.push_back(std::shared_ptr<Section>(new Section(section, valueName, value)));
	}

	save();
}

void INIFiles::write(std::wstring section, std::wstring valueName, std::string value)
{
	std::wstring temp;

	temp.assign(value.begin(), value.end());
	write((std::wstring)section, (std::wstring)valueName, (std::wstring)temp);
}

void INIFiles::write(std::wstring section, std::wstring valueName, wchar_t value)
{
	std::wstring temp;

	temp += value;
	write((std::wstring)section, (std::wstring)valueName, (std::wstring)temp);
}

void INIFiles::write(std::wstring section, std::wstring valueName, const wchar_t* value)
{
	std::wstring temp = value;

	write((std::wstring)section, (std::wstring)valueName, (std::wstring)temp);
}

void INIFiles::write(std::wstring section, std::wstring valueName, char value)
{
	std::string temp1;
	temp1 += value;

	std::wstring temp;
	temp.assign(temp1.begin(), temp1.end());

	write((std::wstring)section, (std::wstring)valueName, (std::wstring)temp);
}

void INIFiles::write(std::wstring section, std::wstring valueName, const char* value)
{
	std::string temp1 = value;
	std::wstring temp;
	temp.assign(temp1.begin(), temp1.end());

	write((std::wstring)section, (std::wstring)valueName, (std::wstring)temp);
}

void INIFiles::write(std::wstring section, std::wstring valueName, int value)
{
	std::wstring temp = std::to_wstring(value);
	write((std::wstring)section, (std::wstring)valueName, (std::wstring)temp);
}

void INIFiles::write(std::wstring section, std::wstring valueName, float value)
{
	std::wstring temp;
	int power = pow(10, precision);

	value *= power;
	int temp1 = value;
	value = temp1 / power;
	temp = std::to_wstring(value);

	write((std::wstring)section, (std::wstring)valueName, (std::wstring)temp);
}

void INIFiles::write(std::wstring section, std::wstring valueName, double value)
{
	std::wstring temp;
	int power = pow(10, precision);

	value *= power;
	int temp1 = value;
	value = temp1 / power;
	temp = std::to_wstring(value);

	write((std::wstring)section, (std::wstring)valueName, (std::wstring)temp);
}

void INIFiles::write(std::wstring section, std::wstring valueName, bool value)
{
	std::wstring temp = (value) ? L"True" : L"False";

	write((std::wstring)section, (std::wstring)valueName, (std::wstring)temp);
}

void INIFiles::write(std::string section, std::string valueName, std::wstring value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	write(sectionTEMP, valueNameTEMP, value);
}

void INIFiles::write(std::string section, std::string valueName, std::string value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	write(sectionTEMP, valueNameTEMP, value);
}

void INIFiles::write(std::string section, std::string valueName, wchar_t value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	write(sectionTEMP, valueNameTEMP, value);
}

void INIFiles::write(std::string section, std::string valueName, const wchar_t* value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	write(sectionTEMP, valueNameTEMP, value);
}

void INIFiles::write(std::string section, std::string valueName, char value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	write(sectionTEMP, valueNameTEMP, value);
}

void INIFiles::write(std::string section, std::string valueName, const char* value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	write(sectionTEMP, valueNameTEMP, value);
}

void INIFiles::write(std::string section, std::string valueName, int value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	write(sectionTEMP, valueNameTEMP, value);
}

void INIFiles::write(std::string section, std::string valueName, float value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	write(sectionTEMP, valueNameTEMP, value);
}

void INIFiles::write(std::string section, std::string valueName, double value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	write(sectionTEMP, valueNameTEMP, value);
}

void INIFiles::write(std::string section, std::string valueName, bool value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	write(sectionTEMP, valueNameTEMP, value);
}

/*---------------------------------------------------------------------------read-----------------------------------------------------------*/
//widestrig
std::wstring INIFiles::read(std::wstring section, std::wstring valueName, std::wstring value)
{
	if (!sections.empty())
	{
		auto sectionInFile = findSection(section);

		if (sectionInFile != NULL)
		{
			if (sectionInFile->existValue(valueName)) return sectionInFile->getValue(valueName);
			else return value;
		}
	}
	return value;
}

std::string INIFiles::read(std::wstring section, std::wstring valueName, std::string value)
{
	std::wstring temp;
	temp.assign(value.begin(), value.end());

	temp = read((std::wstring)section, (std::wstring)valueName, (std::wstring)temp);

	//konwersja z utf-16 (wstring) na ANSII
	value = "";
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	value = converter.to_bytes(temp);

	return value;
}

wchar_t INIFiles::read(std::wstring section, std::wstring valueName, wchar_t value)
{
	std::wstring temp;
	temp += value;

	temp = read((std::wstring)section, (std::wstring)valueName, (std::wstring)temp);
	value = temp[0];
	return value;
}

const wchar_t* INIFiles::read(std::wstring section, std::wstring valueName, const wchar_t* value)
{
	std::wstring temp = value;

	temp = read((std::wstring)section, (std::wstring)valueName, (std::wstring)temp);
	wchar_t* tempc = new wchar_t[temp.size() + 1];
	std::copy(temp.begin(), temp.end(), tempc);
	tempc[temp.size()] = '\0';

	return tempc;
}

char INIFiles::read(std::wstring section, std::wstring valueName, char value)
{
	std::wstring temp;
	std::string temp1;
	temp1 += value;
	temp.assign(temp1.begin(), temp1.end());

	temp = read((std::wstring)section, (std::wstring)valueName, (std::wstring)temp);

	//konwersja z utf-16 (wstring) na ANSII
	temp1 = "";
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	temp1 = converter.to_bytes(temp);

	value = temp1[0];
	return value;
}

const char* INIFiles::read(std::wstring section, std::wstring valueName, const char* value)
{
	std::wstring temp;
	std::string temps = value;

	temp.assign(temps.begin(), temps.end());

	temp = read(section, valueName, temp);
	temps = "";
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	temps = converter.to_bytes(temp);

	char* tempc = new char[temps.size() + 1];
	std::copy(temps.begin(), temps.end(), tempc);
	tempc[temps.size()] = '\0';

	return tempc;
}

int INIFiles::read(std::wstring section, std::wstring valueName, int value)
{
	std::wstring temp = std::to_wstring(value);

	return stoi(read((std::wstring)section, (std::wstring)valueName, (std::wstring)temp));
}

float INIFiles::read(std::wstring section, std::wstring valueName, float value)
{
	std::wstring temp = std::to_wstring(value);
	return stof(read((std::wstring)section, (std::wstring)valueName, (std::wstring)temp));
}

double INIFiles::read(std::wstring section, std::wstring valueName, double value)
{
	std::wstring temp = std::to_wstring(value);
	return std::stod(read((std::wstring)section, (std::wstring)valueName, (std::wstring)temp));
}

bool INIFiles::read(std::wstring section, std::wstring valueName, bool value)
{
	std::wstring temp = (value) ? L"True" : L"False";

	temp = read((std::wstring)section, (std::wstring)valueName, (std::wstring)temp);

	if (boost::to_upper_copy(temp) == boost::to_upper_copy((std::wstring)L"True")) return true;
	if (boost::to_upper_copy(temp) == boost::to_upper_copy((std::wstring)L"False")) return false;
	return value;
}

//String
std::wstring INIFiles::read(std::string section, std::string valueName, std::wstring value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());
	
	return read(sectionTEMP, valueNameTEMP, value);
}

std::string INIFiles::read(std::string section, std::string valueName, std::string value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	return read(sectionTEMP, valueNameTEMP, value);
}

wchar_t INIFiles::read(std::string section, std::string valueName, wchar_t value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	return read(sectionTEMP, valueNameTEMP, value);
}

const wchar_t* INIFiles::read(std::string section, std::string valueName, const wchar_t* value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	return read(sectionTEMP, valueNameTEMP, value);
}

char INIFiles::read(std::string section, std::string valueName, char value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	return read(sectionTEMP, valueNameTEMP, value);
}

const char* INIFiles::read(std::string section, std::string valueName, const char* value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	value = read(sectionTEMP, valueNameTEMP, value);

	return value;
}

int INIFiles::read(std::string section, std::string valueName, int value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	return read(sectionTEMP, valueNameTEMP, value);
}

float INIFiles::read(std::string section, std::string valueName, float value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	return read(sectionTEMP, valueNameTEMP, value);
}

double INIFiles::read(std::string section, std::string valueName, double value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	return read(sectionTEMP, valueNameTEMP, value);
}

bool INIFiles::read(std::string section, std::string valueName, bool value)
{
	std::wstring sectionTEMP, valueNameTEMP;
	sectionTEMP.assign(section.begin(), section.end());
	valueNameTEMP.assign(valueName.begin(), valueName.end());

	return read(sectionTEMP, valueNameTEMP, value);
}