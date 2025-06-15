#include <cstring>
#include <stdexcept>
#include "PromotionMove.h"
#include "PromotionPieceFactory.h"

Piece* PromotionMove::getPiece(Board& board) const
{
	return promotedPiece;
}

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

	PromotionPieceFactory promotionPieceFactory;
	promotedPiece = promotionPieceFactory.createPiece(promotedPieceNotation, color);
}

bool PromotionMove::execute(Game& game)
{
	Board& board = game.getChessVariant().getBoard();
	Piece* promotingPawn = board.at(getFrom());
	PiecesGameInfo& playingSide = game.playingSide();

	if (!Move::execute(game))
	{
		board.deletePiece(promotedPiece);
		board.simulateSetAt(getFrom(), promotingPawn);
		return false;
	}

	playingSide.getPieces().replace(*promotingPawn, *promotedPiece);
	playingSide.indirectAttackersOnOppositeKing().remove(*promotingPawn);

	board.deletePiece(promotingPawn);

	return true;
}
