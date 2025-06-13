#include "EnPassantNotifier.h"

void EnPassantNotifier::notifyGame(const Piece& sender)
{
	const ChessCoordinate& piecePosition = sender.getPosition();

	char col = piecePosition.getCol();
	int row = piecePosition.getRow() - (int)sender.getColor();

	enPassantSquare = ChessCoordinate(col, row);
	
	Game& game = getGame();
	game.setEnPassantSquare(enPassantSquare);
}

void EnPassantNotifier::notifyMove(const Piece& piece)
{
	notifyGame(piece);
}
