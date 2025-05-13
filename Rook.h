#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(PieceColor color);

	char getPieceNotation() const override;
	bool isValidMove(const Move& move) const override;
	wchar_t accept(const PieceRenderer& renderer) const override;
};

