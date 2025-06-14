#pragma once

#include "Move.h"

class CastleMove : public Move
{
public:
	virtual ~CastleMove() = default;

	virtual const ChessCoordinate& kingPosition(PieceColor color) const = 0;
	virtual const ChessCoordinate& rookPosition(PieceColor color) const = 0;

	virtual const ChessCoordinate& initialRookPosition(PieceColor color) const = 0;

	bool execute(Game& game) override;
};

