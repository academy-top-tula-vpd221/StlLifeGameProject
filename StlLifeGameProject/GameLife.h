#pragma once
#include <vector>
#include "Cell.h"
#include "Console.h"
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
	}

	void PrintColony()
	{
		cout << "\n";
		for (auto cell : colony)
		{
			console.WritePosition(cell.Row(), cell.Col(), (char)178);
		}
	}

	bool isColony(Cell cell)
	{
		auto it = find_if(colony.begin(), colony.end(),
			[&cell](Cell item) {
				return (item.Row() == cell.Row()) 
							&& (item.Col() == cell.Col())
							&& (item.State() != CellState::Born);
			});
		return it != colony.end();
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
		for (auto cell = colony.begin(); cell != colony.end(); cell++)
		{
			for (Position diff : Diff)
			{
				Cell candidat(cell->Row() + diff.row, cell->Col() + diff.col, CellState::Born);
				if (!isColony(candidat))
				{
					for (Position diffCand : Diff)
					{
						if (isColony(candidat.Row() + diffCand.row, 
									 candidat.Col() + diffCand.col))
							candidat.Neighbors()++;
					}
					if (candidat.Neighbors() == 3)
						colony.push_back(candidat);
				}
			}
		}
		for (auto it = colony.begin(); it != colony.end(); it++)
		{
			if (it->State() == CellState::Dead)
				colony.erase(it);
			else
				it->State() = CellState::Alive;
			if (colony.size() == 0) break;
		}
			
	}

	void Wait()
	{
		cin.get();
	}
};

