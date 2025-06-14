#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(PieceColor color);

	char getPieceNotation() const override;
	bool isSufficientForWin() const override;
	bool isValidMove(const Move& move) const override;
	void fillDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions) const override;
	wchar_t accept(const PieceRenderer& renderer) const override;

	Piece* clone() const override;
};

