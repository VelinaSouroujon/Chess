#pragma once

#include "IPieceFactory.h"

class PromotionPieceFactory : public IPieceFactory
{
public:
	Piece* createPiece(char pieceNotation, PieceColor color) const override;
};

