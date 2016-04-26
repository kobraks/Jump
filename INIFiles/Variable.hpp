#pragma once
#include <string>
#include <ostream>
#include <vector>
#include <memory>

namespace ini
{
	class Variable
	{
	public:
		Variable();																					//konstruktor domyœlny
		Variable(std::wstring name, std::wstring value);						//Konstruktor je¿eli u¿ywany aby stworzyæ zmienn¹ o koreœlonej nazwie i wartoœci
		Variable(std::wstring line);														//Konstruktor tworz¹cy zmienn¹ z lini
		virtual ~Variable();																	//Destruktor

		void addComment(std::wstring comment);								//Dodaje komentarz do zmiennej
		void deleteComment(int line);													//Usowa komentarz do zmiennej
		void deleteAllComments();														//Usuwa wszystkie komentarze
		void setValue(std::wstring value);												//Ustawia wartoœæ
		void setName(std::wstring name);											//Ustawia nazwê

		std::wstring getName();															//Odczytuje nazwê zmiennej
		std::wstring getValue();															//Odczytuje wartoœæ zmiennej
		std::wstring getComment(int line);											//Odczytuje komentarz w danej lini
		std::vector <std::wstring> getComments();							//Odczytuje wszystkie komentarze
		std::wstring getLine();																//Pobiera linie któr¹ trzeba zapisac do pliku
	private:
		std::wstring name;																	//Nazwa zmiennej
		std::wstring var;																		//Wartoœæ zmiennej
		std::vector <std::shared_ptr<std::wstring>> comments;		//Komentarze do zmiennej

	public:
		friend std::wostream& operator<< (std::wostream& out, Variable& var)
		{
			out << var.getLine() << std::endl;

			if (!var.comments.empty())
			{
				for (auto element : var.comments)
				{
					if (element->at(0) == L';') out << *element << std::endl;
					else out << L";" + *element << std::endl;
				}
			}

			return out;
		}
	};
}
