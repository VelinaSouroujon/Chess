#include <stdexcept>
#include "PiecesGameInfo.h"

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

OneColorPieces& PiecesGameInfo::getPieces()
{
	return pieces;
}

OneColorPieces& PiecesGameInfo::indirectAttackersOnOppositeKing()
{
	return indirectAttackersOnKing;
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
