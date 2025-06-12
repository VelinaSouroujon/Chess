#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(PieceColor color);

	char getPieceNotation() const override;
	bool isValidMove(const Move& move) const override;
	wchar_t accept(const PieceRenderer& renderer) const override;

	Piece* clone() const override;
};

