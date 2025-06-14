#include "Knight.h"
#include "Move.h"
#include "CommonUtils.h"

Knight::Knight(PieceColor color) : Piece(color)
{

}

char Knight::getPieceNotation() const
{
	return Constants::KNIGHT_NOTATION;
}

bool Knight::isSufficientForWin() const
{
	return false;
}

bool Knight::isValidMove(const Move& move) const
{
	if (!Piece::isValidMove(move))
	{
		return false;
	}

	const int MIN_DIFF = 1;
	const int MAX_DIFF = 2;

	const ChessCoordinate& from = move.getFrom();
	const ChessCoordinate& to = move.getTo();

	int rowDiff = CommonUtils::abs(from.getRow() - to.getRow());
	int colDiff = CommonUtils::abs(from.getCol() - to.getCol());

	return (rowDiff == MIN_DIFF && colDiff == MAX_DIFF)
		|| (rowDiff == MAX_DIFF && colDiff == MIN_DIFF);
}

void Knight::fillDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions) const
{
	const int STEPS = 1;

	PieceDirection oneleftTwoUp(-1, 2, STEPS);
	directions.add(oneleftTwoUp);

	PieceDirection oneRightTwoUp(1, 2, STEPS);
	directions.add(oneRightTwoUp);

	PieceDirection twoLeftOneUp(-2, 1, STEPS);
	directions.add(twoLeftOneUp);

	PieceDirection twoRightOneUp(2, 1, STEPS);
	directions.add(twoRightOneUp);


	PieceDirection oneLeftTwoDown(-1, -2, STEPS);
	directions.add(oneLeftTwoDown);

	PieceDirection oneRightTwoDown(1, -2, STEPS);
	directions.add(oneRightTwoDown);

	PieceDirection twoLeftOneDown(-2, -1, STEPS);
	directions.add(twoLeftOneDown);

	PieceDirection twoRightOneDown(2, -1, STEPS);
	directions.add(twoRightOneDown);
}

wchar_t Knight::accept(const PieceRenderer& renderer) const
{
	return renderer.getRepresentation(*this);
}

Piece* Knight::clone() const
{
	return new Knight(*this);
}
