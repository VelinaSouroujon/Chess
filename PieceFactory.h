#pragma once

#include "IPieceFactory.h"
#include "PieceMediator.h"

class PieceFactory : public IPieceFactory
{
private:
	PieceMediator& enPassantMediator;
	PieceMediator& pawnMoveMediator;
	PieceMediator& rookMediator;
	PieceMediator& kingMediator;

public:
	PieceFactory(PieceMediator& enPassantMediator, PieceMediator& pawnMoveMediator, PieceMediator& rookMediator, PieceMediator& kingMediator);

	Piece* createPiece(char pieceNotation, PieceColor color) const override;
};

