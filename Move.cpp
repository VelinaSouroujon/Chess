#include <stdexcept>
#include "Move.h"
#include "CommonUtils.h"
#include "Constants.h"
#include "PieceFactory.h"

void Move::free()
{
	delete piece;
}

Move::Move(const Game& game, const char* notation)
{
	if (notation == nullptr)
	{
		throw std::invalid_argument("Notation cannot be null");
	}

	int notationLength = strlen(notation);

	if (notationLength > Constants::MAX_NOTATION_LENGTH)
	{
		throw std::invalid_argument("Invalid notation length");
	}

	Piece* pieceToMove = nullptr;

	int letterNotationIdx = 1;
	int firstIdx = CommonUtils::toLower(notation[letterNotationIdx]) - 'a';
	int secondIdx = notation[letterNotationIdx + 1] - '0';

	pieceToMove = game.board[firstIdx][secondIdx];

}


Move::~Move()
{
	free();
}

ChessCoordinate Move::getFrom() const
{
	return from;
}

ChessCoordinate Move::getTo() const
{
	return to;
}

bool Move::isCaptureMove() const
{
	return isCapture;
}

Piece* Move::getPromotingPiece(char pieceChar) const
{
	return PieceFactory::createPiece(pieceChar);
}
