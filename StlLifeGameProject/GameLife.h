#pragma once
#include <vector>
#include "Cell.h"
#include "Console.h"
#include <conio.h>
#include <algorithm>

using namespace std;

class GameLife
{
	vector<Cell> colony;
	Console console;
public:
	GameLife(Console console) : console{ console }
	{
		colony.clear();
	}

	void SetColony()
	{
		int row = 0;
		int col = 0;
		console.CursorPosition(row, col);
		KeyCode key;
		bool isExit = false;
		vector<Cell>::iterator it;
		while (true)
		{
			if (_kbhit())
			{
				key = (KeyCode)_getch();
				switch (key)
				{
				case ArrowUp:
					if (row > 0)
						row--;
					break;
				case ArrowRight:
					col++;
					break;
				case ArrowDown:
					row++;
					break;
				case ArrowLeft:
					if (col > 0)
						col--;
					break;
				case Esc:
					isExit = true;
					break;
				case Space:
					Cell candidat = Cell(row, col, CellState::Alive);
					it = isColony(candidat);
					if (it == colony.end())
						colony.push_back(candidat);
					else
						colony.erase(it);
					console.Clear();
					PrintColony();
					break;
					/*case Enter:
						break;
					default:
						break;*/
				}
				console.CursorPosition(row, col * 2);
			}
				
			if (isExit)
				break;
			
		}


		/*
		do
		{
			cout << "input cell? <y/n> ";
			char answer;
			cin >> answer;
			if (answer == 'n')
				break;
			int row, col;
			cout << "input row: ";
			cin >> row;
			cout << "input col: ";
			cin >> col;
			colony.push_back(Cell(row, col, CellState::Alive));
		} while (1);
		*/
	}

	void PrintColony()
	{
		cout << "\n";
		for (auto cell : colony)
		{
			console.WritePosition(cell.Row(), cell.Col()*2, string(2, (char)178));
		}
	}

	vector<Cell>::iterator isColony(Cell cell)
	{
		auto it = find_if(colony.begin(), colony.end(),
			[&cell](Cell item) {
				return (item.Row() == cell.Row()) 
					&& (item.Col() == cell.Col());
			});
		return it;
	}

	bool isColony(int row, int col)
	{
		auto it = find_if(colony.begin(), colony.end(),
			[&](Cell item) {
				return (item.Row() == row) 
							&& (item.Col() == col)
							&& (item.State() != CellState::Born);
			});
		return it != colony.end();
	}

	void Step()
	{
		for (auto cell = colony.begin(); cell != colony.end(); cell++)
		{
			cell->Neighbors() = 0;
			for (Position ncell : Diff)
				if (isColony(cell->Row() + ncell.row, cell->Col() + ncell.col))
					cell->Neighbors()++;
		}
		for (auto cell = colony.begin(); cell != colony.end(); cell++)
			if (cell->Neighbors() < 2 || cell->Neighbors() > 3)
				cell->State() = CellState::Dead;
				//cell.SetState(CellState::Dead);
				//
		for (int i = 0; i < colony.size(); i++)
		{
			for (Position diff : Diff)
			{
				Cell candidat(colony[i].Row() + diff.row, colony[i].Col() + diff.col, CellState::Born);
				if (isColony(candidat) == colony.end())
				{
					for (Position diffCand : Diff)
					{
						Cell tempCell = Cell(candidat.Row() + diffCand.row, candidat.Col() + diffCand.col, CellState::Born);
						auto it = isColony(tempCell);
						if (it != colony.end() && it->State() != CellState::Born)
							candidat.Neighbors()++;
					}
					if (candidat.Neighbors() == 3 && isColony(candidat) == colony.end())
						colony.push_back(candidat);
				}
			}
		}
		for (int i = 0; i < colony.size();)
		{
			if (colony[i].State() == CellState::Dead)
				colony.erase(colony.begin() + i);
			else
			{
				colony[i].State() = CellState::Alive;
				i++;
			}
			if (colony.size() == 0) break;
		}
			
	}

	void Wait()
	{
		cin.get();
	}
};

