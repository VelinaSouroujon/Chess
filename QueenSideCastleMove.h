#pragma once

#include "CastleMove.h"

class QueenSideCastleMove : public CastleMove
{
private:
	const ChessCoordinate whiteKingPosition;
	const ChessCoordinate blackKingPosition;

	const ChessCoordinate whiteRookPosition;
	const ChessCoordinate blackRookPosition;

	const ChessCoordinate whiteInitialRookPosition;
	const ChessCoordinate blackInitialRookPosition;

public:
	QueenSideCastleMove();

	const ChessCoordinate& kingPosition(PieceColor color) const override;
	const ChessCoordinate& rookPosition(PieceColor color) const override;

	const ChessCoordinate& initialRookPosition(PieceColor color) const override;

	bool execute(Game& game) override;
};

