#include <stdexcept>
#include "Piece.h"
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

bool Board::getPathBetweenSameRow(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord, ChessCoordinate* path, int& pathLength) const
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
		CommonUtils::swap(firstCol, secondCol);
	}

	int idxPath = 0;

	for (int col = firstCol + 1; col < secondCol; col++)
	{
		ChessCoordinate squareBetween(col, row);

		path[idxPath] = squareBetween;
		idxPath++;
	}

	pathLength = idxPath;

	return true;
}

bool Board::getPathBetweenSameCol(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord, ChessCoordinate* path, int& pathLength) const
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
		CommonUtils::swap(firstRow, secondRow);
	}

	int idxPath = 0;

	for (int row = firstRow + 1; row < secondRow; row++)
	{
		ChessCoordinate squareBetween(col, row);

		path[idxPath] = squareBetween;
		idxPath++;
	}

	pathLength = idxPath;

	return true;
}

bool Board::getPathBetweenSameDiagonalLeftToRight(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord, ChessCoordinate* path, int& pathLength) const
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
		CommonUtils::swap(firstRow, secondRow);
		col = secondCoord.getCol();
	}

	int idxPath = 0;

	for (int row = firstRow - 1; row > secondRow; row--)
	{
		col++;

		ChessCoordinate squareBetween(col, row);

		path[idxPath] = squareBetween;
		idxPath++;
	}

	pathLength = idxPath;

	return true;
}

bool Board::getPathBetweenSameDiagonalRightToLeft(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord, ChessCoordinate* path, int& pathLength) const
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
		CommonUtils::swap(firstRow, secondRow);
		col = secondCoord.getCol();
	}

	int idxPath = 0;

	for (int row = firstRow - 1; row > secondRow; row--)
	{
		col--;

		ChessCoordinate squareBetween(col, row);

		path[idxPath] = squareBetween;
		idxPath++;
	}

	pathLength = idxPath;

	return true;
}

bool Board::getPathBetweenSameDiagonal(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord, ChessCoordinate* path, int& pathLength) const
{
	return getPathBetweenSameDiagonalLeftToRight(firstCoord, secondCoord, path, pathLength)
		|| getPathBetweenSameDiagonalRightToLeft(firstCoord, secondCoord, path, pathLength);
}

Board::~Board()
{
	for (int i = 0; i < Constants::BOARD_SIZE; i++)
	{
		for (int j = 0; j < Constants::BOARD_SIZE; j++)
		{
			deletePiece(board[i][j]);
		}
	}
}

const Piece* Board::at(const ChessCoordinate& coordinate) const
{
	int rowIdx = getBoardRowIdx(coordinate);
	int colIdx = getBoardColIdx(coordinate);

	return board[rowIdx][colIdx];
}

Piece* Board::at(const ChessCoordinate& coordinate)
{
	int rowIdx = getBoardRowIdx(coordinate);
	int colIdx = getBoardColIdx(coordinate);

	return board[rowIdx][colIdx];
}

void Board::setAt(const ChessCoordinate& coordinate, Piece* piece)
{
	simulateSetAt(coordinate, piece);

	if (piece != nullptr)
	{
		piece->setPosition(coordinate);
	}
}

void Board::simulateSetAt(const ChessCoordinate& coordinate, Piece* piece)
{
	int rowIdx = getBoardRowIdx(coordinate);
	int colIdx = getBoardColIdx(coordinate);

	board[rowIdx][colIdx] = piece;
}

const Piece* Board::at(char col, int row) const
{
	ChessCoordinate coordinate(col, row);

	return at(coordinate);
}

Piece* Board::at(char col, int row)
{
	ChessCoordinate coordinate(col, row);

	return at(coordinate);
}

void Board::setAt(char col, int row, Piece* piece)
{
	ChessCoordinate coordinate(col, row);

	setAt(coordinate, piece);
}

void Board::simulateSetAt(char col, int row, Piece* piece)
{
	ChessCoordinate coordinate(col, row);

	simulateSetAt(coordinate, piece);
}

void Board::deletePiece(Piece*& piece)
{
	delete piece;
	piece = nullptr;
}

bool Board::tryGetPathBetweenTwoSquares(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord, ChessCoordinate* path, int& pathLength) const
{
	return getPathBetweenSameCol(firstCoord, secondCoord, path, pathLength)
		|| getPathBetweenSameRow(firstCoord, secondCoord, path, pathLength)
		|| getPathBetweenSameDiagonal(firstCoord, secondCoord, path, pathLength);
}

bool Board::isPieceBetween(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord) const
{
	const int MAX_PATH_LENGTH = Constants::BOARD_SIZE - 2;
	ChessCoordinate path[MAX_PATH_LENGTH];
	int pathLength = 0;

	bool isTherePath = tryGetPathBetweenTwoSquares(firstCoord, secondCoord, path, pathLength);

	if (!isTherePath)
	{
		return false;
	}

	for (int i = 0; i < pathLength; i++)
	{
		const ChessCoordinate& squareBetween = path[i];

		if (at(squareBetween) != nullptr)
		{
			return true;
		}
	}

	return false;
}

int Board::getSize() const
{
	return Constants::BOARD_SIZE;
}
