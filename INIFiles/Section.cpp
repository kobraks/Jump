#include "Section.hpp"
#include <boost/algorithm/string.hpp>
#include <fstream>

using namespace ini;

Section::Section()
{
}

Section::Section(std::wstring name, std::wstring valueName, std::wstring value)
{
	this->name = name;
	this->variables.push_back(std::shared_ptr<Variable>(new Variable(valueName, value)));
}


Section::~Section()
{
	this->comments.clear();
	this->variables.clear();
}

void Section::setName(std::wstring name)
{
	this->name = name;
}

//---------------------------------------------------------------Values--------------------------------------------------------------

std::wstring Section::getName()
{
	return this->name;
}

auto Section::findVariable(std::wstring name) -> std::shared_ptr<Variable>
{
	std::shared_ptr<Variable> error = NULL;

	for (auto element : this->variables)
	{
		if (boost::to_upper_copy(name) == boost::to_upper_copy(element->getName())) return element;
	}

	return error;
}

std::wstring Section::getValue(std::wstring name)
{
	auto variable = findVariable(name);

	if (variable != NULL) return variable->getValue();

	return L"";
}

void Section::addValue(std::wstring& name, std::wstring& value)
{
	if (this->getValue(name) != L"") this->setValue(name, value);
	else this->variables.push_back(std::shared_ptr<Variable>(new Variable(name, value)));
}

void Section::setValue(std::wstring& name, std::wstring& value)
{
	if (this->getValue(name) == L"") return;
	else
	{
		auto variable = findVariable(name);
		if (variable != NULL) variable->setValue(value);
	}
}

bool Section::existValue(std::wstring  name)
{
	auto variable = findVariable(name);
	if (variable != NULL) return true;

	return false;
}

//---------------------------------------------------------------Comments--------------------------------------------------
void Section::addComment(std::wstring comment)
{
	this->comments.push_back(std::shared_ptr<std::wstring>(new std::wstring(comment)));
}

void Section::addCommentToValue(std::wstring name, std::wstring comment)
{
	if (this->getValue(name) == L"") return;
	else
	{
		auto variable = findVariable(name);
		if (variable != NULL) variable->addComment(comment);
	}
}

void Section::deleteValueComment(std::wstring name, int line)
{
	if (this->getValue(name) == L"") return;
	else
	{
		auto variable = findVariable(name);
		if (variable != NULL) variable->deleteComment(line);
	}
}

void Section::deleteComment(int line)
{
	if (comments.empty()) return;
	else if (line > comments.size()) return;
	else if (line < 0) return;
	else comments.erase(comments.begin() + line);
}

void Section::deleteAllComments()
{
	this->comments.clear();
}

void Section::deleteAllVariableComments(std::wstring name)
{
	auto variable = findVariable(name);
	if (variable != NULL) variable->deleteAllComments();
}

int Section::getNumberOfSectionsInFile(std::wstring name)
{
	int numberOfSection = 0;
	std::wstring temp;

	std::wfstream* file = new std::wfstream(name, std::ios::in);
	if (file->good())
	{
		while (std::getline(*file, temp))
		{
			if (isSectionName(temp)) numberOfSection++;
		}
	}
	else numberOfSection = -1;
	file->close();
	delete file;

	return numberOfSection;
}

bool Section::isSectionName(std::wstring name)
{
	std::wregex pattern(L"\\[(.*?)\\]");
	return std::regex_search(name, pattern);
}