#include "StandardChessVariant.h"

#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

StandardChessVariant::StandardChessVariant(IPieceFactory& iPieceFactory)
	: ChessVariant(iPieceFactory),
	whiteKingInitialPos('e', 1),
	whiteQueenSideRookInitialPos('a', 1),
	whiteKingSideRookInitialPos('h', 1),
	blackKingInitialPos('e', 8),
	blackQueenSideRookInitialPos('a', 8),
	blackKingSideRookInitialPos('h', 8)
{
	Board& board = getBoard();
	const IPieceFactory& pieceFactory = getPieceFactory();

	board.setAt('a', 1, pieceFactory.createPiece(Constants::ROOK_NOTATION, PieceColor::White));
	board.setAt('b', 1, pieceFactory.createPiece(Constants::KNIGHT_NOTATION, PieceColor::White));
	board.setAt('c', 1, pieceFactory.createPiece(Constants::BISHOP_NOTATION, PieceColor::White));
	board.setAt('d', 1, pieceFactory.createPiece(Constants::QUEEN_NOTATION, PieceColor::White));
	board.setAt('e', 1, pieceFactory.createPiece(Constants::KING_NOTATION, PieceColor::White));
	board.setAt('f', 1, pieceFactory.createPiece(Constants::BISHOP_NOTATION, PieceColor::White));
	board.setAt('g', 1, pieceFactory.createPiece(Constants::KNIGHT_NOTATION, PieceColor::White));
	board.setAt('h', 1, pieceFactory.createPiece(Constants::ROOK_NOTATION, PieceColor::White));

	board.setAt('a', 2, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::White));
	board.setAt('b', 2, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::White));
	board.setAt('c', 2, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::White));
	board.setAt('d', 2, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::White));
	board.setAt('e', 2, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::White));
	board.setAt('f', 2, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::White));
	board.setAt('g', 2, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::White));
	board.setAt('h', 2, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::White));


	board.setAt('a', 8, pieceFactory.createPiece(Constants::ROOK_NOTATION, PieceColor::Black));
	board.setAt('b', 8, pieceFactory.createPiece(Constants::KNIGHT_NOTATION, PieceColor::Black));
	board.setAt('c', 8, pieceFactory.createPiece(Constants::BISHOP_NOTATION, PieceColor::Black));
	board.setAt('d', 8, pieceFactory.createPiece(Constants::QUEEN_NOTATION, PieceColor::Black));
	board.setAt('e', 8, pieceFactory.createPiece(Constants::KING_NOTATION, PieceColor::Black));
	board.setAt('f', 8, pieceFactory.createPiece(Constants::BISHOP_NOTATION, PieceColor::Black));
	board.setAt('g', 8, pieceFactory.createPiece(Constants::KNIGHT_NOTATION, PieceColor::Black));
	board.setAt('h', 8, pieceFactory.createPiece(Constants::ROOK_NOTATION, PieceColor::Black));

	board.setAt('a', 7, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::Black));
	board.setAt('b', 7, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::Black));
	board.setAt('c', 7, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::Black));
	board.setAt('d', 7, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::Black));
	board.setAt('e', 7, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::Black));
	board.setAt('f', 7, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::Black));
	board.setAt('g', 7, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::Black));
	board.setAt('h', 7, pieceFactory.createPiece(Constants::PAWN_NOTATION, PieceColor::Black));
}

const ChessCoordinate& StandardChessVariant::kingInitialPos(PieceColor color) const
{
	return color == PieceColor::White
		? whiteKingInitialPos
		: blackKingInitialPos;
}

const ChessCoordinate& StandardChessVariant::queenSideRookInitialPos(PieceColor color) const
{
	return color == PieceColor::White
		? whiteQueenSideRookInitialPos
		: blackQueenSideRookInitialPos;
}

const ChessCoordinate& StandardChessVariant::kingSideRookInitialPos(PieceColor color) const
{
	return color == PieceColor::White
		? whiteKingSideRookInitialPos
		: blackKingSideRookInitialPos;
}
