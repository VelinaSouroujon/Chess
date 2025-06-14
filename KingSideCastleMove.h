#pragma once

#include "CastleMove.h"

class KingSideCastleMove : public CastleMove
{
private:
	const ChessCoordinate whiteKingPosition;
	const ChessCoordinate blackKingPosition;

	const ChessCoordinate whiteRookPosition;
	const ChessCoordinate blackRookPosition;

	const ChessCoordinate whiteInitialRookPosition;
	const ChessCoordinate blackInitialRookPosition;

public:
	KingSideCastleMove();

	const ChessCoordinate& kingPosition(PieceColor color) const override;
	const ChessCoordinate& rookPosition(PieceColor color) const override;

	const ChessCoordinate& initialRookPosition(PieceColor color) const override;

	bool execute(Game& game) override;
};

