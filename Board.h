#pragma once

#include "Piece.h"
#include "Constants.h"
#include "ChessCoordinate.h"

class Board
{
private:
	Piece* board[Constants::BOARD_SIZE][Constants::BOARD_SIZE]{ nullptr };

	int getBoardRowIdx(int row) const;
	int getBoardColIdx(char col) const;

public:
	const Piece* at(const ChessCoordinate& coordinate) const;
	Piece*& at(const ChessCoordinate& coordinate);
	void removeAt(const ChessCoordinate& coordinate);

	bool removeAt(const ChessCoordinate& coordinate);
	int getSize() const;
};

