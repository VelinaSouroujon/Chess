#pragma once

#include "Piece.h"
#include "Board.h"
#include "Moveable.h"

class Pawn : public Piece, public Moveable
{
public:
	Pawn(PieceColor color);

	char getPieceNotation() const override;
	bool isValidMove(const Move& move) const override;
};

