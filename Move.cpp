#include <stdexcept>
#include "Move.h"
#include "CommonUtils.h"
#include "Constants.h"
#include "RookFactory.h"
#include "KnightFactory.h"
#include "BishopFactory.h"
#include "QueenFactory.h"

PieceFactory* Move::pieceCharMap[Constants::ENGLISH_LETTERS_COUNT] = { nullptr };

void Move::initPieceCharMap()
{
	const int FIRST_LETTER = 'A';

	pieceCharMap['R' - FIRST_LETTER] = new RookFactory();
	pieceCharMap['N' - FIRST_LETTER] = new KnightFactory();
	pieceCharMap['B' - FIRST_LETTER] = new BishopFactory();
	pieceCharMap['Q' - FIRST_LETTER] = new QueenFactory();
}

void Move::freePieceCharMap()
{
	for (int i = 0; i < Constants::ENGLISH_LETTERS_COUNT; i++)
	{
		delete pieceCharMap[i];
	}
}

void Move::free()
{
	delete piece;
	freePieceCharMap();
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

	initPieceCharMap();

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
	CommonUtils::toUpper(pieceChar);
	if (!CommonUtils::isInRange(pieceChar, 'A', 'Z'))
	{
		throw std::invalid_argument("Invalid piece character");
	}

	return pieceCharMap[pieceChar - 'A']->create();
}
