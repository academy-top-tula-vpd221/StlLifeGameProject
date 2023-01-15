#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

class Console
{
	std::wstring title;
	HANDLE id;
	COORD currentPosition;
public:
	Console( std::wstring title = L"Console") 
		: title{ title }
	{
		//setlocale(LC_ALL, "Russian");
		id = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTitle((LPCWSTR)title.c_str());
	}

	void WritePosition(int row, int col, std::string str)
	{
		currentPosition.X = col;
		currentPosition.Y = row;
		SetConsoleCursorPosition(id, currentPosition);
		std::cout << str;
	}

	void WritePosition(int row, int col, char symbol)
	{
		currentPosition.X = col;
		currentPosition.Y = row;
		SetConsoleCursorPosition(id, currentPosition);
		std::cout << symbol;
	}

	void Clear()
	{
		system("cls");
	}
};

