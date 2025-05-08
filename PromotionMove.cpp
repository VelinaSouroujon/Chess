#include <cstring>
#include "PromotionMove.h"
#include "PieceFactory.h"

PromotionMove::PromotionMove(const char* notation) : Move(notation)
{
    char promotedPieceNotation = notation[strlen(notation) - 1];
	promotedPiece = PieceFactory::createPiece(promotedPieceNotation);
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
