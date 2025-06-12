#include "Queen.h"
#include "Move.h"

Queen::Queen(PieceColor color) : Piece(color)
{

}

char Queen::getPieceNotation() const
{
	return Constants::QUEEN_NOTATION;
}

bool Queen::isValidMove(const Move& move) const
{
	ChessCoordinate from = move.getFrom();
	ChessCoordinate to = move.getTo();

	return from.isSameRow(to)
		|| from.isSameCol(to)
		|| from.isSameDiagonal(to);
}

wchar_t Queen::accept(const PieceRenderer& renderer) const
{
	return renderer.getRepresentation(*this);
}

Piece* Queen::clone() const
{
	return new Queen(*this);
}
