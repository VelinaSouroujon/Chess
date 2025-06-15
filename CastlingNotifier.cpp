#include <stdexcept>
#include "CastlingNotifier.h"

void CastlingNotifier::notifyGame(const Piece& sender)
{
	Game& game = getGame();
	const ChessVariant& chessVariant = game.getChessVariant();
	const ChessCoordinate& piecePosition = sender.getPosition();
	PieceColor pieceColor = sender.getColor();
	PiecesGameInfo& piecesGameInfo = game.sameColorPiecesInfo(pieceColor);

	if (piecePosition == chessVariant.kingInitialPos(pieceColor))
	{
		if (piecesGameInfo.getKingSideCastlePossible())
		{
			piecesGameInfo.impossibleKingSideCastle();
			game.previousPositionsUnreachable();
		}

		if (piecesGameInfo.getQueenSideCastlePossible())
		{
			piecesGameInfo.impossibleQueenSideCastle();
			game.previousPositionsUnreachable();
		}
	}

	else if (piecePosition == chessVariant.kingSideRookInitialPos(pieceColor)
		&& piecesGameInfo.getKingSideCastlePossible())
	{
		piecesGameInfo.impossibleKingSideCastle();
		game.previousPositionsUnreachable();
	}

	else if (piecePosition == chessVariant.queenSideRookInitialPos(pieceColor)
		&& piecesGameInfo.getQueenSideCastlePossible())
	{
		piecesGameInfo.impossibleQueenSideCastle();
		game.previousPositionsUnreachable();
	}
}

void CastlingNotifier::notifyMove(const Piece& piece)
{
	notifyGame(piece);
}
