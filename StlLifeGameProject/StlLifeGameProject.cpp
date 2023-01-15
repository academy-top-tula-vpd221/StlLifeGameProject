#include <iostream>
#include "Console.h"
#include "GameLife.h"

int main()
{
    Console console(L"Game Life");
	
	char ch;

	GameLife game(console);
	game.SetColony();
	console.Clear();
	game.PrintColony();
	cin >> ch;
	game.Step();
	console.Clear();
	game.PrintColony();
	cin >> ch;
	//game.Wait();
}
