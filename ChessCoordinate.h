#pragma once

#include "Constants.h"

class ChessCoordinate
{
private:
	int row = Constants::MIN_ROW_COORDINATE;
	char col = Constants::MIN_COL_COORDINATE;

public:
	ChessCoordinate() = default;
	ChessCoordinate(char col, int row);

	int getRow() const;
	char getCol() const;

	void setRow(int value);
	void setCol(char value);

	bool isSameRow(const ChessCoordinate& other) const;
	bool isSameCol(const ChessCoordinate& other) const;
	bool isSameDiagonal(const ChessCoordinate& other) const;
	bool isSameDiagonalLeftToRight(const ChessCoordinate& other) const;
	bool isSameDiagonalRightToLeft(const ChessCoordinate& other) const;
	bool isNeighborWith(const ChessCoordinate& other) const;
};

bool operator==(const ChessCoordinate& left, const ChessCoordinate& right);
bool operator!=(const ChessCoordinate& left, const ChessCoordinate& right);
