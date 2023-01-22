#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

enum KeyCode
{
	ArrowUp = 72,
	ArrowRight = 77,
	ArrowDown = 80,
	ArrowLeft = 75,
	Esc = 27,
	Space = 32,
	Enter = 13,
};

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

	void CursorPosition(int row, int col)
	{
		currentPosition.X = col;
		currentPosition.Y = row;
		SetConsoleCursorPosition(id, currentPosition);
	}

	void WritePosition(int row, int col, std::string str)
	{
		CursorPosition(row, col);
		std::cout << str;
	}

	void WritePosition(int row, int col, char symbol)
	{
		CursorPosition(row, col);
		std::cout << symbol;
	}

	void Clear()
	{
		system("cls");
	}
};

