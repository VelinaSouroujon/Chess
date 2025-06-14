#include <stdexcept>
#include "CastlingNotifier.h"

void CastlingNotifier::notifyGame(const Piece& sender)
{
	const ChessVariant& chessVariant = getGame().getChessVariant();
	const ChessCoordinate& piecePosition = sender.getPosition();
	PieceColor pieceColor = sender.getColor();
	PiecesGameInfo& piecesGameInfo = getGame().sameColorPiecesInfo(pieceColor);

	if (piecePosition == chessVariant.kingInitialPos(pieceColor))
	{
		piecesGameInfo.impossibleKingSideCastle();
		piecesGameInfo.impossibleQueenSideCastle();
	}

	else if (piecePosition == chessVariant.kingSideRookInitialPos(pieceColor))
	{
		piecesGameInfo.impossibleKingSideCastle();
	}

	else if (piecePosition == chessVariant.queenSideRookInitialPos(pieceColor))
	{
		piecesGameInfo.impossibleQueenSideCastle();
	}
}

void CastlingNotifier::notifyMove(const Piece& piece)
{
	notifyGame(piece);
}
