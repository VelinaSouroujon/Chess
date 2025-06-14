#include "Queen.h"
#include "Move.h"
#include "Directions.h"

Queen::Queen(PieceColor color) : Piece(color)
{

}

char Queen::getPieceNotation() const
{
	return Constants::QUEEN_NOTATION;
}

bool Queen::isSufficientForWin() const
{
	return true;
}

bool Queen::isValidMove(const Move& move) const
{
	if (!Piece::isValidMove(move))
	{
		return false;
	}

	const ChessCoordinate& from = move.getFrom();
	const ChessCoordinate& to = move.getTo();

	return from.isSameRow(to)
		|| from.isSameCol(to)
		|| from.isSameDiagonal(to);
}

void Queen::fillDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions) const
{
	Directions::fillRowDirections(directions);
	Directions::fillColDirections(directions);
	Directions::fillDiagonalDirections(directions);
}

wchar_t Queen::accept(const PieceRenderer& renderer) const
{
	return renderer.getRepresentation(*this);
}

Piece* Queen::clone() const
{
	return new Queen(*this);
}
