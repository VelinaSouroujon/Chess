#include "StandardChessVariant.h"

#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

StandardChessVariant::StandardChessVariant()
{
	initPiecesOnBoard();
}

void StandardChessVariant::initPiecesOnBoard()
{
	Board& board = getBoardRef();

	board.at('a', 1) = new Rook(PieceColor::White);
	board.at('b', 1) = new Knight(PieceColor::White);
	board.at('c', 1) = new Bishop(PieceColor::White);
	board.at('d', 1) = new Queen(PieceColor::White);
	board.at('e', 1) = new King(PieceColor::White);
	board.at('f', 1) = new Bishop(PieceColor::White);
	board.at('g', 1) = new Knight(PieceColor::White);
	board.at('h', 1) = new Rook(PieceColor::White);

	board.at('a', 2) = new Pawn(PieceColor::White);
	board.at('b', 2) = new Pawn(PieceColor::White);
	board.at('c', 2) = new Pawn(PieceColor::White);
	board.at('d', 2) = new Pawn(PieceColor::White);
	board.at('e', 2) = new Pawn(PieceColor::White);
	board.at('f', 2) = new Pawn(PieceColor::White);
	board.at('g', 2) = new Pawn(PieceColor::White);
	board.at('h', 2) = new Pawn(PieceColor::White);


	board.at('a', 8) = new Rook(PieceColor::Black);
	board.at('b', 8) = new Knight(PieceColor::Black);
	board.at('c', 8) = new Bishop(PieceColor::Black);
	board.at('d', 8) = new Queen(PieceColor::Black);
	board.at('e', 8) = new King(PieceColor::Black);
	board.at('f', 8) = new Bishop(PieceColor::Black);
	board.at('g', 8) = new Knight(PieceColor::Black);
	board.at('h', 8) = new Rook(PieceColor::Black);

	board.at('a', 7) = new Pawn(PieceColor::Black);
	board.at('b', 7) = new Pawn(PieceColor::Black);
	board.at('c', 7) = new Pawn(PieceColor::Black);
	board.at('d', 7) = new Pawn(PieceColor::Black);
	board.at('e', 7) = new Pawn(PieceColor::Black);
	board.at('f', 7) = new Pawn(PieceColor::Black);
	board.at('g', 7) = new Pawn(PieceColor::Black);
	board.at('h', 7) = new Pawn(PieceColor::Black);
}
