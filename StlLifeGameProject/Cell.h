#pragma once
#include <vector>
enum class CellState
{
	Alive,
	Born,
	Dead
};

struct Position
{
	int row;
	int col;
};

std::vector<Position> Diff({ {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} });

class Cell
{
	Position position;
	CellState state;
	int neighbors;
public:
	Cell(Position position, CellState state);
	Cell(int row, int col, CellState state);

	CellState& State() { return state;	}
	void SetState(CellState state) { this->state = state; }
	int& Neighbors() { return neighbors; }
	int Row() { return position.row; }
	int Col() { return position.col; }
};
Cell::Cell(Position position, CellState state)
	: position{ position }, state{ state }, neighbors{} {}
Cell::Cell(int row, int col, CellState state)
	: position{ Position{row, col} }, state{ state }, neighbors{} {}

