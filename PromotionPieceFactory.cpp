#include <stdexcept>
#include "PromotionPieceFactory.h"
#include "CommonUtils.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"

Piece* PromotionPieceFactory::createPiece(char pieceNotation, PieceColor color) const
{
	char upperNotation = CommonUtils::toUpper(pieceNotation);

	switch (upperNotation)
	{
	case Constants::ROOK_NOTATION:
		return new Rook(color);

	case Constants::KNIGHT_NOTATION:
		return new Knight(color);

	case Constants::BISHOP_NOTATION:
		return new Bishop(color);

	case Constants::QUEEN_NOTATION:
		return new Queen(color);

	default:
		throw std::invalid_argument("Invalid piece notation");
	}
}
