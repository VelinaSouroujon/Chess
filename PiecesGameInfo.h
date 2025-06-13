#pragma once

#include "OneColorPieces.h"

class PiecesGameInfo
{
private:
	const Piece* king = nullptr;
	OneColorPieces pieces;
	OneColorPieces indirectAttackersOnKing;

	bool kingSideCastlePossible = true;
	bool queenSideCastlePossible = true;

public:
	PiecesGameInfo(PieceColor color, const Board& board);

	const OneColorPieces& getPieces() const;
	const OneColorPieces& indirectAttackersOnOppositeKing() const;
	const Piece& getKing() const;

	OneColorPieces& getPieces();
	OneColorPieces& indirectAttackersOnOppositeKing();

	void impossibleKingSideCastle();
	void impossibleQueenSideCastle();

	void setKing(const Piece& king);
};

