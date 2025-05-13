#include <cstring>
#include <stdexcept>
#include "PromotionMove.h"
#include "PieceFactory.h"

PromotionMove::PromotionMove(const char* notation) : Move(notation)
{
    char promotedPieceNotation = notation[strlen(notation) - 1];
	int row = getTo().getRow();

	PieceColor color;
	if (row == Constants::BOARD_SIZE)
	{
		color = PieceColor::White;
	}
	else if (row == Constants::MIN_ROW_COORDINATE)
	{
		color = PieceColor::Black;
	}
	else
	{
		throw std::invalid_argument("Invalid row for promotion move.");
	}

	promotedPiece = PieceFactory::createPiece(promotedPieceNotation, color);
}

bool PromotionMove::execute(Board& board) const
{
	if (!Move::execute(board))
	{
		return false;
	}

	board.removeAt(getTo());
	board.at(getTo()) = promotedPiece;

	return true;
}
