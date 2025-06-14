#pragma once

#include "Board.h"
#include "Enums.h"
#include "IPieceFactory.h"

class ChessVariant
{
private:
	Board board;

public:
	virtual ~ChessVariant() = default;

	virtual const ChessCoordinate& kingInitialPos(PieceColor color) const = 0;
	virtual const ChessCoordinate& queenSideRookInitialPos(PieceColor color) const = 0;
	virtual const ChessCoordinate& kingSideRookInitialPos(PieceColor color) const = 0;

	const Board& getBoard() const;
	Board& getBoard();
};

