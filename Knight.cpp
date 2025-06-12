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

bool Knight::isValidMove(const Move& move) const
{
	const int MIN_DIFF = 1;
	const int MAX_DIFF = 2;

	ChessCoordinate from = move.getFrom();
	ChessCoordinate to = move.getTo();

	int rowDiff = CommonUtils::abs(from.getRow() - to.getRow());
	int colDiff = CommonUtils::abs(from.getCol() - to.getCol());

	return (rowDiff == MIN_DIFF && colDiff == MAX_DIFF)
		|| (rowDiff == MAX_DIFF && colDiff == MIN_DIFF);
}

wchar_t Knight::accept(const PieceRenderer& renderer) const
{
	return renderer.getRepresentation(*this);
}

Piece* Knight::clone() const
{
	return new Knight(*this);
}
