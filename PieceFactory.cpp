#include <stdexcept>
#include "PieceFactory.h"
#include "CommonUtils.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"

Piece* PieceFactory::createPiece(char pieceNotation)
{
	char upperNotation = CommonUtils::toUpper(pieceNotation);

	switch (upperNotation)
	{
	case Constants::ROOK_NOTATION:
		return new Rook();

	case Constants::KNIGHT_NOTATION:
		return new Knight();

	case Constants::BISHOP_NOTATION:
		return new Bishop();

	case Constants::QUEEN_NOTATION:
		return new Queen();

	default:
		throw std::invalid_argument("Invalid piece notation");
	}
}
