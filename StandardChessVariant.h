#pragma once

#include "ChessVariant.h"

class StandardChessVariant : public ChessVariant
{
private:
	const ChessCoordinate whiteKingInitialPos;
	const ChessCoordinate whiteQueenSideRookInitialPos;
	const ChessCoordinate whiteKingSideRookInitialPos;

	const ChessCoordinate blackKingInitialPos;
	const ChessCoordinate blackQueenSideRookInitialPos;
	const ChessCoordinate blackKingSideRookInitialPos;

public:
	StandardChessVariant(IPieceFactory& iPieceFactory);

	const ChessCoordinate& kingInitialPos(PieceColor color) const override;
	const ChessCoordinate& queenSideRookInitialPos(PieceColor color) const override;
	const ChessCoordinate& kingSideRookInitialPos(PieceColor color) const override;
};

