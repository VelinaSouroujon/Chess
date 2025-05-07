#pragma once

#include "Piece.h"

class King : public Piece
{
public:
	char getPieceNotation() const override;
	bool isValidMove(const Move& move) const override;
};

