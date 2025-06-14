#include "Bishop.h"
#include "Move.h"
#include "Directions.h"

Bishop::Bishop(PieceColor color) : Piece(color)
{

}

char Bishop::getPieceNotation() const
{
	return Constants::BISHOP_NOTATION;
}

bool Bishop::isSufficientForWin() const
{
	return false;
}

bool Bishop::isValidMove(const Move& move) const
{
	if (!Piece::isValidMove(move))
	{
		return false;
	}

	const ChessCoordinate& from = move.getFrom();
	const ChessCoordinate& to = move.getTo();

	return to.isSameDiagonal(from);
}

void Bishop::fillDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions) const
{
	Directions::fillDiagonalDirections(directions);
}

wchar_t Bishop::accept(const PieceRenderer& renderer) const
{
	return renderer.getRepresentation(*this);
}

Piece* Bishop::clone() const
{
	return new Bishop(*this);
}
