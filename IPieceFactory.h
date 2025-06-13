#pragma once

#include "Piece.h"

class IPieceFactory
{
public:
	virtual ~IPieceFactory() = default;

	virtual Piece* createPiece(char pieceNotation, PieceColor color) const = 0;
};

