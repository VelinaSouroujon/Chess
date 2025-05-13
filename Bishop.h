#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(PieceColor color);

	char getPieceNotation() const override;
	bool isValidMove(const Move& move) const override;
};

