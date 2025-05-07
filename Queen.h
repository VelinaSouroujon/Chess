#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	char getPieceNotation() const override;
	bool isValidMove(const Move& move) const override;
};

