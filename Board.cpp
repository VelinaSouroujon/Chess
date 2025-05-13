#include <stdexcept>
#include "Board.h"
#include "CommonUtils.h"

int Board::getBoardRowIdx(const ChessCoordinate& coordinate) const
{
	return getSize() - coordinate.getRow();
}

int Board::getBoardColIdx(const ChessCoordinate& coordinate) const
{
	return coordinate.getCol() - Constants::MIN_COL_COORDINATE;
}

bool Board::isPieceBetweenSameRow(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord) const
{
	if (!firstCoord.isSameRow(secondCoord))
	{
		return false;
	}

	int row = firstCoord.getRow();
	char firstCol = firstCoord.getCol();
	char secondCol = secondCoord.getCol();

	if (firstCol > secondCol)
	{
		std::swap(firstCol, secondCol);
	}

	for (int col = firstCol + 1; col < secondCol; col++)
	{
		if (at(col, row) != nullptr)
		{
			return true;
		}
	}

	return false;
}

bool Board::isPieceBetweenSameCol(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord) const
{
	if (!firstCoord.isSameCol(secondCoord))
	{
		return false;
	}

	int firstRow = firstCoord.getRow();
	int secondRow = secondCoord.getRow();
	char col = firstCoord.getCol();

	if (firstRow > secondRow)
	{
		std::swap(firstRow, secondRow);
	}

	for (int row = firstRow + 1; row < secondRow; row++)
	{
		if (at(col, row) != nullptr)
		{
			return true;
		}
	}

	return false;
}

bool Board::isPieceBetweenSameDiagonalLeftToRight(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord) const
{
	if (!firstCoord.isSameDiagonalLeftToRight(secondCoord))
	{
		return false;
	}

	char col = firstCoord.getCol();
	int firstRow = firstCoord.getRow();
	int secondRow = secondCoord.getRow();

	if (firstRow < secondRow)
	{
		std::swap(firstRow, secondRow);
		col = secondCoord.getCol();
	}

	for (int row = firstRow - 1; row > secondRow; row--)
	{
		col++;

		if (at(col, row) != nullptr)
		{
			return true;
		}
	}

	return false;
}

bool Board::isPieceBetweenSameDiagonalRightToLeft(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord) const
{
	if (!firstCoord.isSameDiagonalRightToLeft(secondCoord))
	{
		return false;
	}

	char col = firstCoord.getCol();
	int firstRow = firstCoord.getRow();
	int secondRow = secondCoord.getRow();

	if (firstRow < secondRow)
	{
		std::swap(firstRow, secondRow);
		col = secondCoord.getCol();
	}

	for (int row = firstRow - 1; row > secondRow; row--)
	{
		col--;

		if (at(col, row) != nullptr)
		{
			return true;
		}
	}

	return false;
}

bool Board::isPieceBetweenSameDiagonal(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord) const
{
	return isPieceBetweenSameDiagonalLeftToRight(firstCoord, secondCoord)
		|| isPieceBetweenSameDiagonalRightToLeft(firstCoord, secondCoord);
}

const Piece* Board::at(const ChessCoordinate& coordinate) const
{
	int rowIdx = getBoardRowIdx(coordinate);
	int colIdx = getBoardColIdx(coordinate);

	return board[rowIdx][colIdx];
}

Piece*& Board::at(const ChessCoordinate& coordinate)
{
	int rowIdx = getBoardRowIdx(coordinate);
	int colIdx = getBoardColIdx(coordinate);

	return board[rowIdx][colIdx];
}

const Piece* Board::at(char col, int row) const
{
	ChessCoordinate coordinate(col, row);

	return at(coordinate);
}

Piece*& Board::at(char col, int row)
{
	ChessCoordinate coordinate(col, row);

	return at(coordinate);
}

bool Board::isPieceBetween(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord) const
{
	return isPieceBetweenSameCol(firstCoord, secondCoord)
		|| isPieceBetweenSameRow(firstCoord, secondCoord)
		|| isPieceBetweenSameDiagonal(firstCoord, secondCoord);
}

bool Board::removeAt(const ChessCoordinate& coordinate)
{
	if (at(coordinate) == nullptr)
	{
		return false;
	}

	delete at(coordinate);
	at(coordinate) = nullptr;

	return true;
}

int Board::getSize() const
{
	return Constants::BOARD_SIZE;
}
