#include <stdexcept>
#include "PieceFactory.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

PieceFactory::PieceFactory(PieceMediator& enPassantMediator, PieceMediator& pawnMoveMediator, PieceMediator& rookMediator, PieceMediator& kingMediator)
    : enPassantMediator(enPassantMediator),
	pawnMoveMediator(pawnMoveMediator),
	rookMediator(rookMediator),
	kingMediator(kingMediator)
{
}

Piece* PieceFactory::createPiece(char pieceNotation, PieceColor color) const
{
	switch (pieceNotation)
	{
	case Constants::PAWN_NOTATION:
		return new Pawn(color, enPassantMediator, pawnMoveMediator);

	case Constants::ROOK_NOTATION:
		return new Rook(color, &rookMediator);

	case Constants::KNIGHT_NOTATION:
		return new Knight(color);

	case Constants::BISHOP_NOTATION:
		return new Bishop(color);

	case Constants::QUEEN_NOTATION:
		return new Queen(color);

	case Constants::KING_NOTATION:
		return new King(color, kingMediator);

	default:
		throw std::invalid_argument("Invalid piece notation");
	}
}
