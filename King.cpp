#include "King.h"
#include "Move.h"
#include "Directions.h"

King::King(PieceColor color) : Piece(color)
{

}

char King::getPieceNotation() const
{
	return Constants::KING_NOTATION;
}

bool King::isSufficientForWin() const
{
	return false;
}

bool King::isValidMove(const Move& move) const
{
	if (!Piece::isValidMove(move))
	{
		return false;
	}

	const ChessCoordinate& from = move.getFrom();
	const ChessCoordinate& to = move.getTo();

	return from.isNeighborWith(to);
}

void King::fillDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions) const
{
	const int STEPS = 1;

	Directions::fillRowDirections(directions);
	Directions::fillColDirections(directions);
	Directions::fillDiagonalDirections(directions);

	int countDirections = directions.length();

	for (int i = 0; i < countDirections; i++)
	{
		directions[i].setSteps(STEPS);
	}
}

wchar_t King::accept(const PieceRenderer& renderer) const
{
	return renderer.getRepresentation(*this);
}

Piece* King::clone() const
{
	return new King(*this);
}
