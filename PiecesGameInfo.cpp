#include <stdexcept>
#include "PiecesGameInfo.h"
#include "Move.h"

PiecesGameInfo::PiecesGameInfo(PieceColor color, const Board& board)
	: pieces(color, board, king), indirectAttackersOnKing(color)
{

}

const OneColorPieces& PiecesGameInfo::getPieces() const
{
	return pieces;
}

const OneColorPieces& PiecesGameInfo::indirectAttackersOnOppositeKing() const
{
	return indirectAttackersOnKing;
}

const Piece& PiecesGameInfo::getKing() const
{
	if (king == nullptr)
	{
		throw std::logic_error("King is null.");
	}

	return *king;
}

bool PiecesGameInfo::getKingSideCastlePossible() const
{
	return kingSideCastlePossible;
}

bool PiecesGameInfo::getQueenSideCastlePossible() const
{
	return queenSideCastlePossible;
}

OneColorPieces& PiecesGameInfo::getPieces()
{
	return pieces;
}

OneColorPieces& PiecesGameInfo::indirectAttackersOnOppositeKing()
{
	return indirectAttackersOnKing;
}

void PiecesGameInfo::updateAttackers(const ChessCoordinate& newKingPosition)
{
	indirectAttackersOnKing.clear();

	int piecesCount = pieces.getSize();
	const Piece* const* allPieces = pieces.getPieces();

	for (int i = 0; i < piecesCount; i++)
	{
		const Piece* currPiece = allPieces[i];
		const ChessCoordinate& piecePosition = currPiece->getPosition();

		Move move(piecePosition, newKingPosition, true);

		if (currPiece->isValidMove(move))
		{
			indirectAttackersOnKing.add(*currPiece);
		}
	}
}

void PiecesGameInfo::impossibleKingSideCastle()
{
	kingSideCastlePossible = false;
}

void PiecesGameInfo::impossibleQueenSideCastle()
{
	queenSideCastlePossible = false;
}

void PiecesGameInfo::setKing(const Piece& king)
{
	this->king = &king;
}
