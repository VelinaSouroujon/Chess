#pragma once

#include "Piece.h"

class PieceFactory
{
public:
	static Piece* createPiece(char pieceNotation, PieceColor color);
};

