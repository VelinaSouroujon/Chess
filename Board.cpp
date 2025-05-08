#include <stdexcept>
#include "Board.h"
#include "CommonUtils.h"

int Board::getBoardRowIdx(int row) const
{
	return getSize() - row;
}

int Board::getBoardColIdx(char col) const
{
	return col - Constants::MIN_COL_COORDINATE;
}

const Piece* Board::at(const ChessCoordinate& coordinate) const
{
	int rowIdx = getBoardRowIdx(coordinate.getRow());
	int colIdx = getBoardColIdx(coordinate.getCol());

	return board[rowIdx][colIdx];
}

Piece*& Board::at(const ChessCoordinate& coordinate)
{
	int rowIdx = getBoardRowIdx(coordinate.getRow());
	int colIdx = getBoardColIdx(coordinate.getCol());

	return board[rowIdx][colIdx];
}

void Board::removeAt(const ChessCoordinate& coordinate)
{
	delete at(coordinate);
	at(coordinate) = nullptr;
}

int Board::getSize() const
{
	return Constants::BOARD_SIZE;
}
