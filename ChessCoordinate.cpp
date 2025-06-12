#include <stdexcept>
#include "ChessCoordinate.h"
#include "Constants.h"
#include "CommonUtils.h"

ChessCoordinate::ChessCoordinate(char col, int row)
{
	setRow(row);
	setCol(col);
}

char ChessCoordinate::getCol() const
{
    return col;
}

int ChessCoordinate::getRow() const
{
    return row;
}

void ChessCoordinate::setCol(char value)
{
	char lowerCaseValue = CommonUtils::toLower(value);

	if (!CommonUtils::isInRange(lowerCaseValue, Constants::MIN_COL_COORDINATE, Constants::MAX_COL_COORDINATE))
	{
		throw std::out_of_range("Column is out of range");
	}

	col = lowerCaseValue;
}

void ChessCoordinate::setRow(int value)
{
	if (!CommonUtils::isInRange(value, Constants::MIN_ROW_COORDINATE, Constants::BOARD_SIZE))
	{
		throw std::out_of_range("Row is out of range");
	}

	row = value;
}

bool ChessCoordinate::isSameRow(const ChessCoordinate& other) const
{
	return row == other.row;
}

bool ChessCoordinate::isSameCol(const ChessCoordinate& other) const
{
	return col == other.col;
}

bool ChessCoordinate::isSameDiagonal(const ChessCoordinate& other) const
{
	return isSameDiagonalRightToLeft(other)
		|| isSameDiagonalLeftToRight(other);
}

bool ChessCoordinate::isSameDiagonalLeftToRight(const ChessCoordinate& other) const
{
	return col + row == other.col + other.row;
}

bool ChessCoordinate::isSameDiagonalRightToLeft(const ChessCoordinate& other) const
{
	return col - row == other.col - other.row;
}

bool ChessCoordinate::isNeighborWith(const ChessCoordinate& other) const
{
	const int MIN_DIFF = -1;
	const int MAX_DIFF = 1;

	int rowsDiff = row - other.row;
	int colsDiff = col - other.col;

	return CommonUtils::isInRange(rowsDiff, MIN_DIFF, MAX_DIFF)
		&& CommonUtils::isInRange(colsDiff, MIN_DIFF, MAX_DIFF);
}
