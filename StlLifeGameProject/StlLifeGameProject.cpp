#include <iostream>
#include "Console.h"
#include "GameLife.h"
#include <thread>

int main()
{
    Console console(L"Game Life");
	
	char ch;

	GameLife game(console);
	game.SetColony();
	KeyCode key;
	while (true)
	{
		if (_kbhit() && (KeyCode)_getch() == KeyCode::Esc)
			break;
		game.Step();
		console.Clear();
		game.PrintColony();
		this_thread::sleep_for(1000ms);
	}
	
	
	//game.Wait();
}
