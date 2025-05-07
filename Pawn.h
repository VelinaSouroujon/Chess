#pragma once

#include "Piece.h"
#include "Board.h"

class Pawn : public Piece
{
public:
	char getPieceNotation() const override;
	bool isValidMove(const Move& move) const override;
};

