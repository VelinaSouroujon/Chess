#pragma once

#include "Board.h"

class ChessVariant
{
private:
	Board board;

	virtual void initPiecesOnBoard() = 0;

protected:
	Board& getBoardRef();

public:
	virtual ~ChessVariant() = default;

	Board getBoard() const;
};

